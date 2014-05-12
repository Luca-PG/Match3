#pragma once
#include "SDL.h"
#include "GameConfig.h"
#include "GameCell.h"

class GameGrid
{
	public:
		GameGrid(void);
		~GameGrid();

		//check if the cell[x][y] is in a row/column of 3 or more objects of the same type
		int			CheckMatch_Vertical		(int x, int y);
		int			CheckMatch_Horizontal	(int x, int y);

		//the first cell selected by the user
		GameCell *	SelectedCell_1;
		
		//the second cell selected by the user
		GameCell *	SelectedCell_2;

		//multidimensional array of GameCell
		GameCell *	Cells[ROWS][COLUMNS];

		//stores the x,y information of the cell currently selected by the user
		vector2		SelectedPos;

		//check if any cell has been clicked, handles cells selection
		void		HandleInput(SDL_Event * sdlEvent);

		//swap two objects, as requested by the user
		bool		SwapObjects();

		//for each cell, cecks if it is in a row or columns of at least 3 objects of the same type
		//TODO: skip objects already notified to be matching
		bool		FindMatches();

		//The last move is valid, so there is no need for switching back
		void		ValidMove();

		//The last move made by the user is invalid, so the objects are switched back
		void		InvalidMove();

		bool		SwapExecuted;
		
	private:
		//notifies objects to be currently matching
		void		Match_Vertical(int x, int y, int amount);
		void		Match_Horizontal(int x, int y, int amount);

		GameCell *	_previousMove_1;
		GameCell *	_previousMove_2;
		bool		_dragging;
};









