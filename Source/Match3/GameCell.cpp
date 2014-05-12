#include "GameCell.h"

GameCell::GameCell(int x, int y)
{
	this->Position.x = GRID_OFFSET_X + x;
	this->Position.y = GRID_OFFSET_Y + y;
	this->Object = 0;
}

void GameCell::SetObject(IGridObject * obj)
{
	this->Object = obj;
	if(this->Object != 0)
		this->Object->Move(&Position);
}

bool GameCell::HandleEvents(SDL_Event * sdlEvent)
{
    int x = 0, y = 0;

    x = sdlEvent->button.x;
    y = sdlEvent->button.y;

    if( ( x > Position.x ) && ( x < Position.x + SIZE_UNIT ) && ( y > Position.y ) && ( y < Position.y + SIZE_UNIT ) )
    {
		return true;
    }
    
	return false;

}