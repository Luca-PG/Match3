#pragma once
#include "Gem.h"
#include "GameConfig.h"
#include "SDL.h"
#include <queue>
using namespace std;

//a wrapper for a queue of Gems, adds some safety when popping.
//TODO: convert to a template
class GemPool
{
public:
	GemPool(void);
	~GemPool();

	Gem * GetElement( GemType gemType );
	void  Recycle( Gem * g );
};

