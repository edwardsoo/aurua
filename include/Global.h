#pragma once
#include <GL/gl.h>
#include <GL/glut.h>

// Day of year
extern float day[9];

extern float progress[9];

extern float DAYS[9];
extern bool isTimeProgressing;

extern float getPlanetLocation(int planet);

extern float speedFactor[10];

extern void updateDay(int planet) ;

extern void toggleTime();

extern GLuint raw_texture_load(const char *filename, int width, int height);

#define SKY 0
