#pragma once
#include "SDL.h"

//screen attributes
const int SCREEN_WIDTH	= 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP	= 32;

//frame limit, to avoid spikes and inconsistency in performance
const int FRAMES_PER_SECOND = 60;

//game grid attributes
const int ROWS = 8;
const int COLUMNS = 8;

//size, in pixel, of the gem images, and so of the grid cells
const int SIZE_UNIT = 40; 

//offset used to move the grid and its contents on different positions on the screen
const int GRID_OFFSET_X = 365;
const int GRID_OFFSET_Y = 116;

//time to execute a movement/animation, expressed in milliseconds
const int ANIMATION_TIME = 500; 

//one minute
const int END_GAME_TIMER = 1000 * 60; 

//coordinate and size of every frame of the gems texture
const SDL_Rect Rect_Gem_Blue	= {   0,0,40,40} ;
const SDL_Rect Rect_Gem_Green	= {  40,0,40,40} ;
const SDL_Rect Rect_Gem_Purple	= {  80,0,40,40} ;
const SDL_Rect Rect_Gem_Red		= { 120,0,40,40} ;
const SDL_Rect Rect_Gem_Yellow	= { 160,0,40,40} ;

struct vector2
{
    int x;
    int y;
};

enum GemType
{
	Type_Invalid = 0,
	Type_Blue,
	Type_Green,
	Type_Purple,
	Type_Red,
	Type_Yellow
};


enum GameStatus
{
	Status_Find_Matches,
	Status_Activate_Matches,
	Status_Move_Gems_Down,
	Status_Wait_For_Animation,
	Status_Reset_Input,
	Status_Wait_For_Input,
	Status_Wait_For_InputAnimation,
	Status_Starting_Up,
	Status_Quitting
};