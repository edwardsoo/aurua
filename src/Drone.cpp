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

#include "SphereProxy.h"

Drone::Drone(Vec3 _pos, Vec3 _vel, Vec3 _acc) :
		Character(_pos, _vel, _acc, 3, 50, 100) {
	proxy = new SphereProxy(this, DRONE_RADIUS / 2);
}

Drone::~Drone() {
	delete proxy;
}

Vec3 Drone::get_proxy_pos() {
	return pos + Vec3(0, DRONE_HOVER_HEIGHT, 0);
}

void Drone::draw() {
	glPushMatrix();
	glTranslatef(0, DRONE_HOVER_HEIGHT, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(.5, 20, 20);
	glTranslatef(0, 0, -.5);
	glColor3f(0, 1, 0);
	glutSolidSphere(.3, 20, 20);
	glTranslatef(0, 0, .5);
	glScalef(1, 0.2, 1);
	glColor3f(1, 0, 0);
	glutSolidCube(4);
	glPopMatrix();
}
