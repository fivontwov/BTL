#ifndef GAME_BASE_
#define GAME_BASE_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define MIX_CHANNEL -1


#define BASE_OFFSET_SPEED 0

#define VELOCITY 1000

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2
const std::string WINDOW_TITLE = "Flappy Bird";

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 522;

const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 57;
const int SMALL_BUTTON_HEIGHT = 57;
const int CHARACTER_WIDTH = 80;
const int CHARACTER_HEIGHT = 70;

const int PLAY_BUTON_POSX = 560;
const int PLAY_BUTTON_POSY= 205;
const int EXIT_BUTTON_POSX = 560;
const int EXIT_BUTTON_POSY = 415;
const int HELP_BUTTON_POSX = 560;
const int HELP_BUTTON_POSY = 310;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.5;
const double LAYER_8_SPEED = 1.75;
const double LAYER_9_SPEED = 2.0;

const int FLYING_FRAMES = 15;
const int BACKGROUND_LAYER = 9;
const int TOTAL_FOOD = 5;
const int BOOM_FRAME = 4;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};


#endif // !GAME_LIB_
