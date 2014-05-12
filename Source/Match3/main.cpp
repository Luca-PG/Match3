#include "SDL.h"
#include "SDLHelper.h"
#include "Gem.h"
#include <memory>
#include <vector>
#include "gameGrid.h"
#include "GemPool.h"
#include "GemFactory.h"
#include <cmath>
using namespace std;

//the game loop nehaves differently depending on the actual game status
void ResolveGameplayStatus();

//Resolves the matches. Gem objects are recycled, Cells are left empty.
void RemoveMatches();

//Check the grid for empty cells, starting from the bottom-right corner. Everytime it finds an empty cell it moves down, if possible, the gem from the above cell.
//If one of the top cells is empty, then gets a new gem from the GemFactory
void MoveGemsDown();

//Check if the gems have finished moving
bool AnimationFinished(int elapsedTime);

//Draws all graphic elements
bool Draw();

//Initializes and loads all classes and resources used in the game loop
bool InitAndLoadResources();

//deletes textures
void UnloadResources();


GameGrid	* gameGrid		= 0;
GemFactory	* gemFactory	= 0;
SDL_Surface * background	= 0;
SDL_Surface * foreground	= 0;
SDL_Surface * cursor		= 0;

SDL_Event	sdlEvent;
GameStatus	Status			= Status_Starting_Up;
int			elapsedTime		= 0;
int			animationTime	= 0;
int			endGameTimer	= 0;

int main( int argc, char* args[] )
{
    InitAndLoadResources();

	int lastFrameTicks = 0;
	int frameTicks	= 0 ;

    //The game loop starts here
    while( Status != Status_Quitting ) 
    {
		endGameTimer += elapsedTime;

		//abruptly ends the game after 60 seconds
		//TODO: visualize a timer, start a different match.
		if(endGameTimer > END_GAME_TIMER)
			Status = Status_Quitting;

		//Calculate elapsed time (ticks) since last loop 
		 frameTicks = SDL_GetTicks();
		 elapsedTime = frameTicks - lastFrameTicks;
		 lastFrameTicks = frameTicks;

        //Check for quit event
        while( SDL_PollEvent( &sdlEvent ) )
        {
            if( sdlEvent.type == SDL_QUIT )
            {
                Status = Status_Quitting;
            }
        }

		ResolveGameplayStatus();

		Draw();


		//limit the frame rate, to avoid spikes and inconsistency in performance
		//TODO: computations and rendering should be made on different threads
		frameTicks = SDL_GetTicks() - frameTicks;
        if( frameTicks < 1000 / FRAMES_PER_SECOND )
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - (frameTicks) );

    }

	UnloadResources();

    SDL_Quit();
    
    return 0;    
}

void ResolveGameplayStatus()
{
	switch(Status)
	{
		//Initial state
		case Status_Starting_Up :
		{
			Status = Status_Find_Matches;
		}break;

		//Enter this state after moving down the gems, or after user input
		case Status_Find_Matches :
		{
			if(gameGrid->FindMatches())
			{
				gameGrid->ValidMove();
				Status = Status_Activate_Matches;
			}
			else
			{
				gameGrid->InvalidMove();
				Status = Status_Wait_For_InputAnimation;
			}
		}break;

		//Enter this state if there are any matches
		case Status_Activate_Matches :
		{
			RemoveMatches();
			Status = Status_Move_Gems_Down;
		}break;

		//Enter this state after removing gems from the grid
		case Status_Move_Gems_Down :
		{
			MoveGemsDown();
			Status = Status_Wait_For_Animation;
		}break;

		//Enter this state after dropping down new gems, wait for the animation to finish before checking for new matches
		case Status_Wait_For_Animation :
		{
			if(AnimationFinished(elapsedTime))
			{
				Status = Status_Find_Matches;
			}

		}break;

			
		//Enter this state after ivalid user input, wait for the animation to finish before letting the user make a new move
		case Status_Wait_For_InputAnimation :
		{
			if(AnimationFinished(elapsedTime))
			{
				Status = Status_Wait_For_Input;
			}

		}break;

		//Idle, listening for user input
		default:
		case Status_Wait_For_Input:
		{
			gameGrid->HandleInput( &sdlEvent );
			if(gameGrid->SwapObjects())
			{
				Status = Status_Wait_For_Animation;
			}
		}break;
	}
}

bool Draw()
{
		//Draw foreground
		ApplySurface( 0, 0, background, Screen(), NULL );

		//Draw cursor
		if(gameGrid->SelectedCell_1 != 0)
			ApplySurface( gameGrid->SelectedCell_1->Position.x, gameGrid->SelectedCell_1->Position.y, cursor, Screen(), NULL );

		//Draw and update gems. 
		//TODO: Update code should be separated
		for( int i=0; i < ROWS; i++ )
		{
			for( int j=0; j < COLUMNS; j++ )
			{
				Gem * g = static_cast<Gem *>( gameGrid->Cells[i][j]->Object );
				if( g != NULL )
				{
					g->UpdateMovement( elapsedTime );
					g->Show();
				}
			}
		}
		
		//Draw the foreground
		ApplySurface( 0, 0, foreground, Screen(), NULL );

		//Present the screen
		if( SDL_Flip( Screen() ) == -1 )
		{
			return 1;
		}
}

bool InitAndLoadResources()
{
	if( SDLInit() == false )
    {
        return 1;
    }

	gameGrid	= new GameGrid();
	gemFactory	= new GemFactory( 2*ROWS*COLUMNS );

    background = LoadImage( "Images\\background.png" );
    foreground = LoadImage( "Images\\foreground.png" );
    cursor = LoadImage( "Images\\cursor.png" );
	
	
	for( int i=0; i < ROWS; i++ )
	{
		for( int j=0; j < COLUMNS; j++ )
		{
			gameGrid->Cells[i][j]->SetObject( gemFactory->GetGem() );
		}
	}
}

void UnloadResources()
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( foreground );
    SDL_FreeSurface( cursor );
}



void RemoveMatches()
{
	for( int i=0; i < ROWS; i++ )
	{
		for( int j=0; j < COLUMNS; j++ )
		{
			if(gameGrid->Cells[i][j]->Object->IsMatching)
			{
				Gem * g = static_cast<Gem *>( gameGrid->Cells[i][j]->Object);
				gemFactory->RecycleGem( g );
				gameGrid->Cells[i][j]->Object = 0;
			}
		}
	}	
}

void MoveGemsDown()
{
	bool movingDown = true;

	while(movingDown)
	{
		movingDown = false;
		for( int i=ROWS-1; i > 0; i-- )
		{
			for( int j=COLUMNS-1; j >= 0; j-- )
			{
				if(gameGrid->Cells[i][j]->Object == 0)
				{
					if(gameGrid->Cells[i-1][j]->Object != 0)
					{
						gameGrid->Cells[i][j]->SetObject( gameGrid->Cells[i-1][j]->Object );
						gameGrid->Cells[i-1][j]->Object = 0;
						movingDown = true;
					}
				}
			}
		}	

		for( int j=COLUMNS-1; j >= 0; j-- )
		{
			if(gameGrid->Cells[0][j]->Object == 0)
			{
				gameGrid->Cells[0][j]->SetObject( gemFactory->GetGem() );
				movingDown = true;
			}
		}

	}

}

bool AnimationFinished (int elapsedTime)
{
	animationTime += elapsedTime;

	if(animationTime > ANIMATION_TIME)
	{
		animationTime = 0;
		return true;	
	}

	return false;
}
