#if defined(__APPLE_CC__)
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#elif defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdint.h>
#endif

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "JPEG.h"
#include "ViewingMode.h"
#include "Ship.h"
#include "Global.h"
#include "Camera.h"
#include "Vec3.h"
#include "Utils.h"

using namespace std;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Global State Variables ///////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// time increment between calls to idle() in ms,
// currently set to 30 FPS
//float dt = 1000.0f * 1.0f / 60.0f;

// flag to indicate that we should clean up and exit
bool is_quit = false;

// Keys variables
bool key_states[256];

bool special_states[256];

// window handles
int main_window, cam_window;
unsigned long prev_time;
int frame_passed = 0;
char win_title[32] = { 0 };

static GLuint texture;
unsigned int texture_array[3];

// display width and height
int disp_width = 800, disp_height = 640;

Camera cam;

// Cursor previous position
int prev_x, prev_y;

//Cool debug tool! Use command line arguments to pass in ints!
bool is_use_in_values = false;
double in_value[3];
double cam_rot_speed = 1.0;
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Initialization/Setup and Teardown ////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// set up opengl state, allocate objects, etc.  This gets called
// ONCE PER WINDOW, so don't allocate your objects twice!
void init() {
	/////////////////////////////////////////////////////////////
	/// TODO: Put your initialization code here! ////////////////
	/////////////////////////////////////////////////////////////
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH ), glutGet(GLUT_WINDOW_HEIGHT ));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	// lighting stuff
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat specular[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat position0[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	GLfloat position1[] = { -1.0, -1.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);

}

// free any allocated objects and return
void cleanup() {
	/////////////////////////////////////////////////////////////
	/// TODO: Put your teardown code here! //////////////////////
	/////////////////////////////////////////////////////////////

}

const int DIMENSIONS = 3;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Callback Stubs ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// window resize callback
void resize_callback(int width, int height) {
	/////////////////////////////////////////////////////////////
	/// TODO: Put your resize code here! ////////////////////////
	/////////////////////////////////////////////////////////////
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH ), glutGet(GLUT_WINDOW_HEIGHT ));
	glutPostRedisplay();
}

/*void resetCurrentMatrix() {
 for (int x = 0; x < 16; x++) {
 currentMatrix[x] = 0;
 }
 }*/

// keyboard callback
void keyboard_callback(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		is_quit = true;
		return;
	case 'p':
		toggleTime();
		return;
	default:
		break;
	}
}

void special_key_callback(int key, int x, int y) {
	special_states[key] = !special_states[key];
}

void cam_keyboard_callback(unsigned char key, int x, int y) {
	key_states[key] = true;
}

void cam_keyup_callback(unsigned char key, int x, int y) {
	key_states[key] = false;
	fflush(stdout);
}

void keys_consumer() {
	if (key_states[27]) {
		is_quit = true;
		return;
	}

	double speed = 0.015;
#if _WIN32
	// return states of the left shift key
	if (GetKeyState(VK_LSHIFT) & 0x80) {
		speed = 1.0;
	}
#endif

	// Camera view relative vectors
	Vec3 cam_f;
	if (!special_states[GLUT_KEY_F1]) {
		cam_f = Vec3(cam.view.x, 0, cam.view.z);
	} else {
		cam_f = cam.view;
	}
	cam_f.normalize();
	Vec3 cam_r = cam_f.cross(cam.up);
	cam_r.normalize();

	Vec3 cam_dir(0, 0, 0);
	if (key_states['w']) {
		cam_dir += cam_f;
	} else if (key_states['s']) {
		cam_dir -= cam_f;
	}
	if (key_states['d']) {
		cam_dir += cam_r;
	} else if (key_states['a']) {
		cam_dir -= cam_r;
	}
	if (cam_dir != Vec3(0, 0, 0)) {
		// debug_vec3(&cam_dir);
		cam_dir.normalize();
	}

	cam.pos += cam_dir * speed;
}

// motion callback
void motion_callback(int x, int y) {
	int current_window = glutGetWindow();
	double dx, dy;

	if (current_window == cam_window) {
		int mid_x = glutGet(GLUT_WINDOW_WIDTH ) >> 1;
		int mid_y = glutGet(GLUT_WINDOW_HEIGHT ) >> 1;

		dx = x - mid_x;
		dy = y - mid_y;

// glutWrapPointer has a bug where it may call the MotionCallback again
		if (dx == 0 && dy == 0) {
			return;
		}
		glutWarpPointer(mid_x, mid_y);

		double x_rad = cam_rot_speed * dx / disp_width;
		double y_rad = cam_rot_speed * dy / disp_height;

		cam.rotate_view(x_rad, y_rad);
		/*
		 if (dx != 0 || dy != 0) {
		 printf("dx=%f dy=%f ", x_rad, y_rad);
		 debug_vec3(&cam.view);
		 fflush(stdout);
		 }*/
	}
}

void modelChildShip() {
	glPushMatrix();
	glutSolidSphere(.5, 20, 20);
	glTranslatef(0, 0, -.5);
	glColor3f(0, 1, 0);
	glutSolidSphere(.3, 20, 20);
	glTranslatef(0, 0, .5);
	glScalef(1, 0.2, 1);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
}

/* drawTexturedSphere(r, segs) - Draw a sphere centered on the local
 origin, with radius r and approximated by segs polygon segments,
 having texture coordinates with a latitude-longitude mapping.
 */
void drawTexturedSphere(float r, int segs) {
	int i, j;
	float x, y, z, z1, z2, R, R1, R2;

	// Top cap
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.5f, 1.0f); // This is an ugly (u,v)-mapping singularity
	glVertex3f(0, 0, r);
	z = cos(M_PI / segs);
	R = sin(M_PI / segs);
	for (i = 0; i <= 2 * segs; i++) {
		x = R * cos(i * 2.0 * M_PI / (2 * segs));
		y = R * sin(i * 2.0 * M_PI / (2 * segs));
		glNormal3f(x, y, z);
		glTexCoord2f((float) i / (2 * segs), 1.0f - 1.0f / segs);
		glVertex3f(r * x, r * y, r * z);
	}
	glEnd();

	// Height segments
	for (j = 1; j < segs - 1; j++) {
		z1 = cos(j * M_PI / segs);
		R1 = sin(j * M_PI / segs);
		z2 = cos((j + 1) * M_PI / segs);
		R2 = sin((j + 1) * M_PI / segs);
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= 2 * segs; i++) {
			x = R1 * cos(i * 2.0 * M_PI / (2 * segs));
			y = R1 * sin(i * 2.0 * M_PI / (2 * segs));
			glNormal3f(x, y, z1);
			glTexCoord2f((float) i / (2 * segs), 1.0f - (float) j / segs);
			glVertex3f(r * x, r * y, r * z1);
			x = R2 * cos(i * 2.0 * M_PI / (2 * segs));
			y = R2 * sin(i * 2.0 * M_PI / (2 * segs));
			glNormal3f(x, y, z2);
			glTexCoord2f((float) i / (2 * segs), 1.0f - (float) (j + 1) / segs);
			glVertex3f(r * x, r * y, r * z2);
		}
		glEnd();
	}

	// Bottom cap
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0.5f, 1.0f); // This is an ugly (u,v)-mapping singularity
	glVertex3f(0, 0, -r);
	z = -cos(M_PI / segs);
	R = sin(M_PI / segs);
	for (i = 2 * segs; i >= 0; i--) {
		x = R * cos(i * 2.0 * M_PI / (2 * segs));
		y = R * sin(i * 2.0 * M_PI / (2 * segs));
		glNormal3f(x, y, z);
		glTexCoord2f(1.0f - (float) i / (2 * segs), 1.0f / segs);
		glVertex3f(r * x, r * y, r * z);
	}
	glEnd();
}

void draw_hemisphere(int slices, int stacks) {
	float i, j;
	for (i = 0; i <= stacks; i++) {
		// Compute 2 heights z of strip, and distances xz_r from center
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / (2 * stacks));
		double z0 = sin(lat0);
		double xy_r0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double) i / (2 * stacks));
		double z1 = sin(lat1);
		double xy_r1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= slices; j++) {
			double lng = 2 * M_PI * (double) (j - 1) / slices;
			double x = cos(lng);
			double y = sin(lng);

			// glTexCoordf()
			glNormal3f(x * xy_r0, y * xy_r0, z0);
			glTexCoord2f((j - 1) / slices, 1.0 - (i / stacks));
			glVertex3f(x * xy_r0, y * xy_r0, z0);

			// glTexCoordf()
			glNormal3f(x * xy_r1, y * xy_r1, z1);
			glTexCoord2f((j) / slices, 1.0 - (i / stacks));
			glVertex3f(x * xy_r1, y * xy_r1, z1);
		}
		glEnd();
	}
}

void draw_scene() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 5, 10);
	modelChildShip();
	glPopMatrix();
	draw_grid();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);

	// Draw textured sky hemisphere
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture_array[SKY]);
	glScalef(1000, 1000, 1000);
	draw_hemisphere(128, 128);
	//drawTexturedSphere(100, 64);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

// increment frame_passed every call, update FPS value every one second
void set_fps() {
	unsigned long curr_time = get_system_time();
	int current_window = glutGetWindow();
	if (current_window == cam_window) {
		frame_passed++;
		if (curr_time - prev_time > 1000.0) {
			sprintf(win_title, "%d fps", (int) frame_passed);
			glutSetWindowTitle(win_title);
			frame_passed = 0;
			prev_time = curr_time;
		}
	}

}

// display callback
void display_callback(void) {
	double tmp[16];
	int current_window = glutGetWindow();
	keys_consumer();

// clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!special_states[GLUT_KEY_F2]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f,
			float(glutGet(GLUT_WINDOW_WIDTH ))
					/ float(glutGet(GLUT_WINDOW_HEIGHT )), 0.1f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Vec3 center = cam.pos + cam.view;
	gluLookAt(cam.pos.x, cam.pos.y, cam.pos.z, center.x, center.y, center.z,
			cam.up.x, cam.up.y, cam.up.z);
	draw_scene();

	/*
	 glGetDoublev(GL_MODELVIEW_MATRIX, tmp);
	 printMatrix(tmp);
	 */
	glutSetWindow(current_window);
	glutSwapBuffers();
	set_fps();
}

void draw_title() {
	glEnable(GL_TEXTURE_2D);

	/* create a square on the XY
	 note that OpenGL origin is at the lower left
	 but texture origin is at upper left
	 => it has to be mirrored
	 (gasman knows why i have to mirror X as well) */

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);

	double rect_length_x;
	double rect_length_y;

	if (is_use_in_values) {
		rect_length_x = in_value[0];
		rect_length_y = in_value[1];
	} else {
		rect_length_x = 1.0;
		rect_length_y = 1.0;
	}

	glNormal3f(0.0, 0.0, 1.0);

	glTexCoord2d(1, 1);
	glVertex3f(-rect_length_x, -rect_length_y, 0.0);
	glTexCoord2d(1, 0);
	glVertex3f(-rect_length_x, rect_length_y, 0.0);
	glTexCoord2d(0, 0);
	glVertex3f(rect_length_x, rect_length_y, 0.0);
	glTexCoord2d(0, 1);
	glVertex3f(rect_length_x, -rect_length_y, 0.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void render() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* fov, aspect, near, far */
	gluPerspective(60, 1, 1, 10);
	gluLookAt(0, 0, -2, /* eye */
	0, 0, 2, /* center */
	0, 1, 0); /* up */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.2, 0.2, 0.2, 0.2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSolidCube(1);
	draw_title();

	glPopAttrib();

	glFlush();

	glutSwapBuffers();
}

void idle() {
	if (is_quit) {
// cleanup any allocated memory
		cleanup();
// perform hard exit of the program, since glutMainLoop()
// will never return
		exit(0);
	}

	glutSetWindow(main_window);
	glutPostRedisplay();

	glutSetWindow(cam_window);
	glutPostRedisplay();

}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Program Entry Point //////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {

	if (argc == 4) {
		is_use_in_values = true;
		for (int x = 1; x < 4; x++) {
			cout << "a" << argv[x];
			in_value[x - 1] = strtod(argv[x], NULL);
		}
	} else {
		for (int x = 0; x < 3; x++) {
			in_value[x] = 0;
		}
	}

	cam = Camera();
	cam.pos = Vec3(0, 5, 0);
	cam.view = Vec3(0, 0, 1);
	cam.up = Vec3(0, 1, 0);

// initialize glut
	glutInit(&argc, argv);

// use double-buffered RGB+Alpha framebuffers with a depth buffer.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

// initialize the mothership window
	glutInitWindowSize(disp_width, disp_height);
	glutInitWindowPosition(0, 100);
	main_window = glutCreateWindow("AURUA");
	glutKeyboardFunc(keyboard_callback);
	glutDisplayFunc(render);
	glutReshapeFunc(resize_callback);

// initialize the camera window
	glutInitWindowSize(disp_width, disp_height);
	glutInitWindowPosition(disp_width + 50, 100);
	cam_window = glutCreateWindow("Camera");
	glutKeyboardFunc(cam_keyboard_callback);
	glutKeyboardUpFunc(cam_keyup_callback);
	glutSpecialFunc(special_key_callback);
	glutDisplayFunc(display_callback);
	glutReshapeFunc(resize_callback);
	glutPassiveMotionFunc(motion_callback);
	glutMotionFunc(motion_callback);
	JPEG_Texture(texture_array, "sky_map.jpg", SKY);

	glutSetWindow(main_window);
	init();
	glutSetWindow(cam_window);
	glutSetCursor(GLUT_CURSOR_NONE);
	init();

	texture = raw_texture_load("aurua.raw", 1772, 1772);

	glutIdleFunc(idle);

// start the main loop
	glutMainLoop();

	return 0;
}
