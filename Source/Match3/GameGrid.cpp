#include "GameGrid.h"

GameGrid::GameGrid(void)
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j<COLUMNS; j++)
		{
			Cells[i][j] = new GameCell(j*SIZE_UNIT,i*SIZE_UNIT);
		}
	}

	SelectedCell_1	= 0;
	SelectedCell_2	= 0;
	_previousMove_1  = 0;
	_previousMove_2  = 0;
	SelectedPos.x	= -1;
	SelectedPos.y	= -1;
	SwapExecuted	= false;
}


int _previousMouseX;
int _previousMouseY;

int GameGrid::CheckMatch_Horizontal(int x, int y)
{
	int iMatch = 0;

	if(Cells[x][y]->Object == 0)
		return iMatch;

	int iterator = 1;
	while (((y + iterator) < ROWS) && (Cells[x][y]->Object->Type() == Cells[x][y+iterator]->Object->Type() ))
	{
		iterator++;
	}
	if(iterator > 2)
	{
		iMatch = iterator;
		Match_Horizontal(x,y,iterator);
	}
	
	return iMatch;
}

void GameGrid::Match_Horizontal(int x, int y, int amount)
{
	for (int j = y; j < y+amount; j++)
	{
		Cells[x][j]->Object->Match();
	}
}

int GameGrid::CheckMatch_Vertical(int x, int y)
{
	int iMatch = 0;
	
	if(Cells[x][y]->Object == 0)
		return iMatch;

	int iterator = 1;
	while (((x + iterator) < COLUMNS) && (Cells[x][y]->Object->Type() == Cells[x+iterator][y]->Object->Type() ))
	{
		iterator++;
	}
	if(iterator > 2)
	{
		iMatch = iterator;
		Match_Vertical(x,y,iterator);
	}

	return iMatch;
}

void GameGrid::Match_Vertical(int x, int y, int amount)
{
	for (int j = x; j < x+amount; j++)
	{
		Cells[j][y]->Object->Match();
	}
}

GameGrid::~GameGrid()
{
	for(int i=0; i<ROWS; i++)
	{
		delete[] Cells[i];
	}

	delete[] Cells;
}

void  GameGrid::HandleInput(SDL_Event * sdlEvent)
{
	if( sdlEvent->type == SDL_MOUSEBUTTONUP)
    {
		_dragging = false;
	}

	if( sdlEvent->type == SDL_MOUSEBUTTONDOWN && sdlEvent->button.button == SDL_BUTTON_LEFT)
    {		
		for( int i=0; i < ROWS; i++ )
		{
			for( int j=0; j < COLUMNS; j++ )
			{
				if(Cells[i][j]->HandleEvents(sdlEvent))
				{
					if( SelectedCell_1 == 0 )
					{
						SelectedCell_1 = Cells[i][j];
						SelectedPos.x = i;
						SelectedPos.y = j;
						_dragging = true;
						_previousMouseX = sdlEvent->motion.x;
						_previousMouseY = sdlEvent->motion.y;
					}
					else if 
						( 
							( SelectedCell_1 != Cells[i][j] )
							&& 
							(
								((abs (SelectedPos.x - i) <= 1 ) && (abs (SelectedPos.y - j) == 0 ))
								|| ((abs (SelectedPos.y - j) <= 1 ) && (abs (SelectedPos.x - i) == 0 ))
							)
						)
					{
						SelectedCell_2 = Cells[i][j];
					}
					else
					{
						SelectedCell_1 = Cells[i][j];
						SelectedPos.x = i;
						SelectedPos.y = j;
						_dragging = true;
						_previousMouseX = sdlEvent->motion.x;
						_previousMouseY = sdlEvent->motion.y;
					}

				}
			}
		}
	}
	/*
	if( Dragging && sdlEvent->type == SDL_MOUSEMOTION )
    {		
		if (_previousMouseX - sdlEvent->motion.x > SIZE_UNIT/3)
		{
			SelectedCell_2 = Cells[SelectedPos.x+1][SelectedPos.y];
		}
		else if (sdlEvent->motion.x - _previousMouseX > SIZE_UNIT/3)
		{
			SelectedCell_2 = Cells[SelectedPos.x-1][SelectedPos.y];
		}
		else if (_previousMouseY - sdlEvent->motion.y > SIZE_UNIT/3)
		{
			SelectedCell_2 = Cells[SelectedPos.x][SelectedPos.y+1];
		}
		else if (sdlEvent->motion.y - _previousMouseY > SIZE_UNIT/3)
		{
			SelectedCell_2 = Cells[SelectedPos.x][SelectedPos.y-1];
		}

	}*/

}

void GameGrid::ValidMove()
{
	_previousMove_1 = 0;
	_previousMove_2 = 0;
}

void GameGrid::InvalidMove()
{
	if(_previousMove_1 != 0 && _previousMove_2 != 0)
	{
		IGridObject * obj = _previousMove_1->Object;
		_previousMove_1->SetObject ( _previousMove_2->Object );
		_previousMove_2->SetObject ( obj );
	}
}

bool GameGrid::SwapObjects()
{
	SwapExecuted = false;
	if ( SelectedCell_1 != 0 && SelectedCell_2 != 0)
	{
		SwapExecuted = true;
		IGridObject * obj = SelectedCell_1->Object;
		SelectedCell_1->SetObject ( SelectedCell_2->Object );
		SelectedCell_2->SetObject ( obj );
		_previousMove_1 = SelectedCell_1;
		_previousMove_2 = SelectedCell_2;
		SelectedCell_1 = 0;
		SelectedCell_2 = 0;
		SelectedPos.x = -1;
		SelectedPos.y = -1;
	}

	return SwapExecuted;
}

bool GameGrid::FindMatches()
{
	int iMatches = 0;
	for( int i=0; i < ROWS; i++ )
	{
		for( int j=0; j < COLUMNS; j++ )
		{
			iMatches += CheckMatch_Vertical(i,j);
			iMatches += CheckMatch_Horizontal(i,j);
		}
	}

	return iMatches > 0 ? true : false;
}

