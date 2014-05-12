#pragma once
#include "SDL.h"
#include "GameConfig.h"

//An interface to be implemented by any class that has to interact with a GameGrid
class IGridObject
{
	public:
		virtual ~IGridObject() {}

		//true when the object is in a row or column of at least 3 objects of the same type
		bool IsMatching;

		//invoked when the object is in a row or column of at least 3 objects of the same type, so when IsMatching becames true
		virtual void Match() = 0;

		//invoked when the object is moved from a cell to another one
		virtual void Move( vector2 *) = 0;

		//used to check if object are of the same type
		virtual int  Type() = 0;
};

//The basic piece of the GameGrid, used to identify different positions on the grid, move grid objects around consistently, determine if 
//it has been clicked.
class GameCell
{
	public:
		GameCell(int x, int y);

		vector2			Position;
		IGridObject *	Object;
		void			SetObject(IGridObject *);
		bool			HandleEvents(SDL_Event * sdlEvent);
};