#ifndef MAIN_H_
#define MAIN_H_

// Texture ID
#define TITLE 0
#define SKY_Q1 TITLE+1
#define SKY_Q2 SKY_Q1+1
#define SKY_Q3 SKY_Q2+1
#define SKY_Q4 SKY_Q3+1
#define NUM_TEXTURES SKY_Q4+1

// Display list ID
#define SKY_LIST 1

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
unsigned long prev_time;
int frame_passed = 0;
char win_title[32] = { 0 };

// Textures variables
GLuint textures[NUM_TEXTURES];

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

#endif
