#include "Ship.h"
#include "ViewingMode.h"
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
#include "Global.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

Ship::Ship(void)
{
	reset();
}


void Ship::reset(void) {
	viewingMode = LOOKAT;
	for (int x = 0; x < 3; x++) {
		eyePoint[x] = EYE_POINT[x];
		lookAtPoint[x] = LOOK_AT_POINT[x];
		upVector[x] = UP_VECTOR[x];
	}
	speedMultiplier = 1;
	yaw = 0;
	pitch = 0;
	roll = 0;
	offset = 0;
	planet = 2;
	shipProgress = 0;
	orbitOffset = 0;
}

void Ship::changeViewingMode() {
	switch (viewingMode) {
		case LOOKAT:
			gluLookAt(eyePoint[0],eyePoint[1],eyePoint[2],
				lookAtPoint[0],lookAtPoint[1],lookAtPoint[2],
				upVector[0], upVector[1], upVector[2]);
			break;
		case FLYING:
			glTranslatef(0, 0, offset);
			//pitch
			glRotated(pitch, 1, 0, 0);

			//yaw
			glRotated(yaw, 0, 1, 0);

			//roll
			glRotated(roll, 0, 0, 1);
			offset = 0;
			pitch = 0;
			yaw = 0;
			roll = 0;
			glMultMatrixd(currentMatrix);
			break;
		case ORBIT:
			if (isTimeProgressing) {
				shipProgress++;
				if (shipProgress > 99) {
					shipProgress = 0;
				}
			}

			float prog = shipProgress / 100.0f;
			float p = prog * 2 * 3.141592653589793238462643383279;
			glTranslatef(0, 0, orbitOffset);
			glRotatef(prog * 360 - 180, 0, -1.0, 0);
			glTranslatef(ORBIT_RADIUS * sin(p), 0, ORBIT_RADIUS * cos(p));
			glRotatef(-45, 1.0, 0, 0);
			glRotatef(-90, 0, 1.0, 0);
			glTranslatef(-getPlanetLocation(planet), 0, 0);
			glRotatef(progress[planet] * 360, 0, -1.0, 0);
			
			break;
	}
}

void Ship::changeRelative(double* d, bool isPositive) {
	double factor;
	if (isPositive) {
		factor = .1;
	} else {
		factor = -.1;
	}
	*d += factor * speedMultiplier;
}

void Ship::changeLook(double* f, bool isPositive, int axis) {
	changeRelative(f + axis, isPositive);
}

void Ship::changeSpeed(bool isPositive) {
	int factor;
	if (isPositive) {
		factor = 1;
	} else {
		factor = -1;
	}
	int newMultiplier = speedMultiplier + factor;
	if (newMultiplier < 1) {
		newMultiplier = 1;
	}
	speedMultiplier = newMultiplier;
}

/**
	Handles Flying key commands. Return true if something was done.
*/
bool Ship::flyingKeyHandler(unsigned char key) {
	 switch( key ){
		case 'q':
			changeFlying(&yaw, true);
			break;
		case 'e':
			changeFlying(&yaw, false);
			break;
		
		case 'x':
			changeFlying(&pitch, true);
			break;
		case 'c':
			changeFlying(&pitch, false);
			break;

		case 'a':
			changeFlying(&roll, true);
			break;
		case 'd':
			changeFlying(&roll, false);
			break;

		case 'w':
			changeFlying(&offset, true);
			break;
		case 's':
			changeFlying(&offset, false);
			break;
        default:
            return false;
    }
    return true;
}

/**
	Handles LookAt key commands. Return true if something was done.
*/
bool Ship::lookAtKeyHandler(unsigned char key) {
	 switch( key ){
		case 'a': case 'b': case 'c':
			changeLook(lookAtPoint, true, key - 'a');
			break;
		case 'A': case 'B': case 'C':
			changeLook(lookAtPoint, false, key - 'A');
			break;
		case 'd': case 'e': case 'f':
			changeLook(upVector, true, key - 'd');
			break;
		case 'D': case 'E': case 'F':
			changeLook(upVector, false, key - 'D');
			break;
		case 'x': case 'y': case 'z':
			changeLook(eyePoint, true, key - 'x');
			break;
		case 'X': case 'Y': case 'Z':
			changeLook(eyePoint, false, key - 'X');
			break;
        default:
            return false;
    }
    return true;
}

bool Ship::orbitKeyHandler(unsigned char key) {
	switch (key) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			planet = key - '1';
			return true;
		case 'w':
			orbitOffset += 0.1 * speedMultiplier;
			if (orbitOffset >= ORBIT_RADIUS) {
				orbitOffset = ORBIT_RADIUS;
			}
			return true;
		case 's':
			orbitOffset -= 0.1 * speedMultiplier;
			return true;
		default:
			return false;
	}
}

// keyboard callback
void Ship::keyboardCallback(unsigned char key) {
	bool wasHandled = false;
	switch (viewingMode) {
		case LOOKAT:
			wasHandled = lookAtKeyHandler(key);
			break;
		case FLYING:
			wasHandled = flyingKeyHandler(key);
			break;
		case ORBIT:
			wasHandled = orbitKeyHandler(key);
			break;
	}

	if (wasHandled) {
		return;
	}

    switch( key ){
		case 'l':
			reset();
			viewingMode = LOOKAT;
			break;
		case 'r':
			reset();
			//resetCurrentMatrix();
			viewingMode = FLYING;
			break;
		case 'g':
			reset();
			viewingMode = ORBIT;
			break;
		case 'm':
			reset();
			break;

		case '=':
			changeSpeed(true);
			break;
		case '-':
			changeSpeed(false);
        default:
            break;
    }
}

void Ship::changeFlying(double* aspect, bool isPositive) {
	*aspect = (isPositive) ? speedMultiplier : - speedMultiplier;
}

Ship::~Ship(void)
{
}
