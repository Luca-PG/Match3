#pragma once
#include "SDL.h"
#include "SDL_Image.h"	
#include "GameConfig.h"
#include <string>

SDL_Surface * Screen();

//Initializes all SDL subsystems, the rendering screen, and the window title.
bool SDLInit();

//Loads any image type; supports image alpha. Images must be in the same folder as main.cpp
SDL_Surface * LoadImage( std::string filename );

//Render a portion (defined by the "clip" argument) of the source image to the destination surface, at position (x:y).
void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, const SDL_Rect* clip );

