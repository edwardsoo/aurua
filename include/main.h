#ifndef MAIN_H_
#define MAIN_H_

#include "Game.h"

bool sky_init = false;

//The number of milliseconds to which the timer is set
const int TIMER_MS = 16;

// flag to indicate that we should clean up and exit
bool is_quit = false;
bool paused = false;

// Keys variables
bool key_states[256];
bool special_states[256];

// window handles
int main_window, cam_window;
unsigned long prev_fps_time;
unsigned long prev_phys_time;
int frame_passed = 0;
char win_title[32] = { 0 };



// display width and height
int disp_width = 800, disp_height = 640;

// Cursor previous position
int prev_x, prev_y;

//Cool debug tool! Use command line arguments to pass in ints!
bool is_use_in_values = false;
double in_value[3];
double cam_rot_speed = 1.0;

void idle(int);
void motion_callback(int x, int y);

Game game;

#endif
