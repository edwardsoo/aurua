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

#include "ViewingMode.h"
#include "Ship.h"
#include "Global.h"
#include "Camera.h"
#include "Vec3.h"

using namespace std;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Global State Variables ///////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// time increment between calls to idle() in ms,
// currently set to 30 FPS
float dt = 1000.0f * 1.0f / 60.0f;

// flag to indicate that we should clean up and exit
bool is_quit = false;

// window handles for mother ship and scout ship
int main_window, cam_window;

static GLuint texture;

// display width and height
int disp_width = 800, disp_height = 640;

Ship mother_ship;
Ship child_ship;
Camera cam;

// Cursor previous position
int prev_x, prev_y;

//Cool debug tool! Use command line arguments to pass in ints!
bool is_use_in_values = false;
double in_value[3];
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

// inversion routine originally from MESA
bool invert_pose(float *m);

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

void drawAxis() {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
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
	mother_ship.keyboardCallback(key);
}

// motion callback
void motion_callback(int x, int y) {
	int current_window;
	double dx, dy;
	GLint vp[4];

	glGetIntegerv(GL_VIEWPORT, vp);
	int mid_x = vp[2] >> 1;
	int mid_y = vp[3] >> 1;

	dx = x - mid_x;
	dy = y - mid_y;

	glutWarpPointer(mid_x, mid_y);

/*
	if (dx != 0 || dy != 0) {
		printf("current window: %d\n", current_window);
		printf("x=%d y=%d prev_x=%d prev_y=%d dx=%f dy=%f\n", x, y, prev_x,
				prev_y, dx, dy);
		printf("cam view: %f, %f, %f\n", cam.view[0], cam.view[1], cam.view[2]);
	}*/

	double x_rad = dx / disp_width;
	double y_rad = dy / disp_height;

	cam.view[2] = cam.pos[2] + (sin(x_rad) * gaze[0] + cos(x_rad) * gaze[2]);
	cam.view[0] = cam.pos[0] + (cos(x_rad) * gaze[0] - sin(x_rad) * gaze[2]);
	cam.view[2] = cam.pos[2] + (sin(y_rad) * gaze[1] + cos(y_rad) * gaze[2]);
	cam.view[1] = cam.pos[0] + (cos(y_rad) * gaze[1] - sin(y_rad) * gaze[2]);

//	printf("viewport: %d %d %d %d, pos_x %d pos_y %d\n", vp[0], vp[1], vp[2],
//			vp[3], pos_x, pos_y);
	glutPostRedisplay();
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

void draw_scene() {
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 10);
	modelChildShip();
}

// display callback
void display_callback(void) {
	double tmp[16];
	int current_window;
	// retrieve the currently active window
	current_window = glutGetWindow();

	// clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	/////////////////////////////////////////////////////////////
	/// TODO: Put your rendering code here! /////////////////////
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f,
			float(glutGet(GLUT_WINDOW_WIDTH ))
					/ float(glutGet(GLUT_WINDOW_HEIGHT )), 0.1f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.pos[0], cam.pos[1], cam.pos[2], cam.view[0], cam.view[1],
			cam.view[2], cam.up[0], cam.up[1], cam.up[2]);
	/*
	printf("pos %f %f %f view %f %f %f up %f %f %f \n", cam.pos[0], cam.pos[1],
				cam.pos[2], cam.view[0], cam.view[1], cam.view[2], cam.up[0],
				cam.up[1], cam.up[2]);
*/

	glGetDoublev(GL_MODELVIEW_MATRIX, tmp);
	printf("%f %f %f %f\n%f %f %f %f\n %f %f %f %f\n%f %f %f %f\n\n", 
	tmp[0], tmp[4], tmp[8], tmp[12], tmp[1], tmp[5], tmp[9], tmp[13],tmp[2], tmp[6], tmp[10], tmp[14],
	tmp[3], tmp[7], tmp[11], tmp[15]);

	draw_scene();

	// swap the front and back buffers to display the scene
	//glutSetWindow(current_window);
}

// not exactly a callback, but sets a timer to call itself
// in an endless loop to update the program
void idle() {

	// if the user wants to quit the program, then exit the
	// function without resetting the timer or triggering
	// a display update
	if (is_quit) {
		// cleanup any allocated memory
		cleanup();

		// perform hard exit of the program, since glutMainLoop()
		// will never return
		exit(0);
	}

	/////////////////////////////////////////////////////////////
	/// TODO: Put your idle code here! //////////////////////////
	/////////////////////////////////////////////////////////////

	// set the currently active window to the mothership and
	// request a redisplay
	glutSetWindow(main_window);
	glutPostRedisplay();
	glutSetWindow(cam_window);
	glutPostRedisplay();

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
	//glutDisplayFunc(display_callback);
	glutReshapeFunc(resize_callback);
	glutSetWindow(main_window);
	init();

	// initialize the camera window
	glutInitWindowSize(disp_width, disp_height);
	glutInitWindowPosition(disp_width + 50, 100);
	cam_window = glutCreateWindow("Camera");
	glutKeyboardFunc(keyboard_callback);
	glutDisplayFunc(display_callback);
	glutReshapeFunc(resize_callback);
	glutMotionFunc(motion_callback);
	glutSetWindow(cam_window);

	texture = raw_texture_load("aurua.raw", 1772, 1772);

	glutIdleFunc(idle);

	// start the blug main loop
	glutMainLoop();

	return 0;
}

bool invert_pose(float *m) {
	float inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15]
			+ m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15]
			- m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15]
			+ m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14]
			- m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15]
			- m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15]
			+ m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15]
			- m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14]
			+ m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15]
			+ m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15]
			- m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15]
			+ m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14]
			- m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11]
			- m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11]
			+ m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11]
			- m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10]
			+ m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		m[i] = inv[i] * det;

	return true;
}
