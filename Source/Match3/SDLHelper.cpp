#include "SDLHelper.h"

//If SDLInit is not called before any other method, then those methods will return 
bool _isInitialized = false;

SDL_Surface * _screen;

SDL_Surface * Screen()
{
	return _screen;
}

SDL_Surface * LoadImage( std::string filename )
{
	if(!_isInitialized)
		return NULL;

    SDL_Surface* loadedImage	= 0;
    SDL_Surface* optimizedImage = 0;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != 0 )
    {
        //Create an optimized surface, so the old one is not needed anymore and set free
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, const SDL_Rect* clip = 0  )
{
	if(!_isInitialized)
		return;

    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, const_cast<SDL_Rect*>(clip), destination, &offset );
}



bool SDLInit()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    _screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( _screen == NULL )
    {
        return false;
    }

    SDL_WM_SetCaption( "Match 3 Game prototype", NULL );

	_isInitialized = true;
    return true;
}
