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

#include "main.h"
#include "ViewingMode.h"
#include "Global.h"
#include "Camera.h"
#include "Vec3.h"
#include "Utils.h"
#include "Geometry.h"

using namespace std;

Camera cam;
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

void draw_sky() {
	// Draw textured sky hemisphere
	if (!sky_init) {
		glNewList(SKY_LIST, GL_COMPILE_AND_EXECUTE);
		glEnable(GL_TEXTURE_2D);
		glScalef(1000, 1000, 1000);
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, textures[SKY_Q1]);
		draw_quarter_hemisphere(1, 64);
		glRotatef(90, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, textures[SKY_Q2]);
		draw_quarter_hemisphere(1, 64);
		glRotatef(90, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, textures[SKY_Q3]);
		draw_quarter_hemisphere(1, 64);
		glRotatef(90, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, textures[SKY_Q4]);
		draw_quarter_hemisphere(1, 64);
		glDisable(GL_TEXTURE_2D);
		glEndList();
		sky_init = true;
	} else {
		glCallList(SKY_LIST);
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
	draw_sky();
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

void draw_HUD() {

	// Draw HUDs
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw_crosshair(glutGet(GLUT_WINDOW_WIDTH ), glutGet(GLUT_WINDOW_HEIGHT ));
}

void draw_3D() {
	glEnable(GL_DEPTH_TEST);

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

	/*
	 float tmp[16];glPushMatrix();
	 glGetFloatv(GL_MODELVIEW_MATRIX, tmp);
	 invert_pose(tmp);
	 glMultMatrixf(tmp);
	 glPopMatrix();*/

	draw_scene();

}

// display callback
void display_callback(void) {
	int current_window = glutGetWindow();
	keys_consumer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_3D();
	draw_HUD();

	glutSetWindow(current_window);
	glutSwapBuffers();
	set_fps();
}

void draw_title() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[TITLE]);

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

void create_textures() {
	raw_texture_load(textures, "textures/aurua.raw", 1772, 1772, TITLE);
	raw_texture_load(textures, "textures/sky_q1.raw", 512, 512,
	SKY_Q1);
	raw_texture_load(textures, "textures/sky_q2.raw", 512, 512,
	SKY_Q2);
	raw_texture_load(textures, "textures/sky_q3.raw", 512, 512,
	SKY_Q3);
	raw_texture_load(textures, "textures/sky_q4.raw", 512, 512,
	SKY_Q4);
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
	glutSetWindow(main_window);
	init();

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
	glutSetWindow(cam_window);
	glutSetCursor(GLUT_CURSOR_NONE);
	init();

	// load image and create textures
	create_textures();

	glutIdleFunc(idle);

// start the main loop
	glutMainLoop();

	return 0;
}
