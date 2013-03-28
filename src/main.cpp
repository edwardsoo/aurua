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

// window handles for mother ship and scout ship
int main_window, cam_window;

static GLuint texture;

// display width and height
int disp_width = 800, disp_height = 640;

Camera cam;

// Cursor previous position
int prev_x, prev_y;

//Cool debug tool! Use command line arguments to pass in ints!
bool is_use_in_values = false;
double in_value[3];
double cam_speed = 1.0;
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

		double x_rad = cam_speed * dx / disp_width;
		double y_rad = cam_speed * dy / disp_height;

		Vec3 view_xz = Vec3(cam.view.z, 0, cam.view.z);
		cam.view.z = (sin(x_rad) * cam.view.x + cos(x_rad) * cam.view.z);
		cam.view.x = (cos(x_rad) * cam.view.x - sin(x_rad) * cam.view.z);
		cam.view.y = (cos(y_rad) * cam.view.y - sin(y_rad) * view_xz.length());
		cam.view.normalize();
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

void draw_scene() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 5, 10);
	modelChildShip();
	glPopMatrix();
	draw_grid();
}

// display callback
void display_callback(void) {
	double tmp[16];
	int current_window = glutGetWindow();

	// clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	glutKeyboardFunc(keyboard_callback);
	glutDisplayFunc(display_callback);
	glutReshapeFunc(resize_callback);
	glutPassiveMotionFunc(motion_callback);
	glutMotionFunc(motion_callback);

	glutSetWindow(main_window);
	init();
	glutSetWindow(cam_window);
	init();

	texture = raw_texture_load("aurua.raw", 1772, 1772);

	glutIdleFunc(idle);

	// start the main loop
	glutMainLoop();

	return 0;
}
