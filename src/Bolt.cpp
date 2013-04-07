/*
 * Bolt.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: Edward
 */

#include "Bolt.h"

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

Bolt::Bolt(Vec3 _pos, Vec3 _vel, Vec3 _acc) :
		Object(_pos, _vel, _acc, 0) {
	// TODO Auto-generated constructor stub

}

Bolt::~Bolt() {
	// TODO Auto-generated destructor stub
}

void Bolt::draw() {
	glPushMatrix();
	glColor4f(1.0, 0, 0, 0.5);
	glutSolidSphere(BOLT_RADIUS, 16, 16);
	glPopMatrix();
}

