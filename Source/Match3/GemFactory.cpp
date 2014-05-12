#include "GemFactory.h"
#include <random>



int gridCenter = GRID_OFFSET_X + (SIZE_UNIT*(COLUMNS/2));

GemFactory::GemFactory(int gemsAmount)
{
	_gemTexture = LoadImage( "Images\\gems.png" );

	_gemPool = new GemPool();

	for(int i=0;i<gemsAmount;i++)
	{
		_gemPool->Recycle( new Gem(gridCenter,-GRID_OFFSET_Y-SIZE_UNIT,SIZE_UNIT,SIZE_UNIT, _gemTexture));
	}
}

GemFactory::~GemFactory()
{
    SDL_FreeSurface( _gemTexture );

	delete _gemPool;
}

Gem * GemFactory::GetGem()
{
    std::random_device rd;
    std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 4);

	switch(dis(gen))
	{
		default:
		case 0:	  return _gemPool->GetElement( Type_Blue	);
		case 1:	  return _gemPool->GetElement( Type_Green	);
		case 2:	  return _gemPool->GetElement( Type_Purple	);
		case 3:	  return _gemPool->GetElement( Type_Red		);
		case 4:	  return _gemPool->GetElement( Type_Yellow	);
	}
}

void GemFactory::RecycleGem(Gem * g)
{
	g->Bounds.x = gridCenter;
	g->Bounds.y = -GRID_OFFSET_Y-SIZE_UNIT;
	g->IsMatching = false;
	_gemPool->Recycle( g );
}
