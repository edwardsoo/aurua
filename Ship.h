#pragma once
#include "ViewingMode.h"

const double EYE_POINT[3] = { 0, 10, 10 };
const double LOOK_AT_POINT[3] = { 0, 0, 0 };
const double UP_VECTOR[3] = { 0, 1, 0 };

const float ORBIT_RADIUS = 1.5;
class Ship
{
public:
	Ship();

	~Ship(void);

	void reset(void);
	void changeViewingMode(void);

	void changeRelative(double* d, bool isPositive);
	void changeLook(double* f, bool isPositive, int axis);

	void changeSpeed(bool isPositive);
/*
	Handles Flying key commands. Return true if something was done.
*/
	bool flyingKeyHandler(unsigned char key);
	bool lookAtKeyHandler(unsigned char key);
	bool orbitKeyHandler(unsigned char key);
	void keyboardCallback(unsigned char key);
	void changeFlying(double* aspect, bool isPositive);

	ViewingMode viewingMode;

	double eyePoint[3];
	double lookAtPoint[3];
	
	double upVector[3];
	int speedMultiplier;

	double currentMatrix[16];

	double yaw;
	double pitch;
	double roll;
	double offset;

	int planet;

	int shipProgress;
	float orbitOffset;
};

