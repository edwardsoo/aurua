/*
 * Drone.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: Edward
 */

#include "Drone.h"

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

Drone::Drone(Vec3 _pos, Vec3 _vel, Vec3 _acc) :
		Character(_pos, _vel, _acc, 1, 1, 50, 100) {
}

Drone::~Drone() {
	// TODO Auto-generated destructor stub
}

void Drone::draw() {
	glPushMatrix();
	glColor3f(1, 1, 1);
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
