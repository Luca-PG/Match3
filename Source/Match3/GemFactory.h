#pragma once
#include "Gem.h"
#include "SDL.h"
#include "SDLHelper.h"
#include "GemPool.h"
#include "GameConfig.h"


//Allocates a maximum number of gems during initialization.
//Offers methods to get and recycle gems
class GemFactory
{
	public:
	GemFactory(int gemsAmount);

	~GemFactory();

	//Uses normal distribution to generate a gem of a random type
	Gem *	GetGem();

	//Recycles a gem for future use, and resets its game logic attributes
	void	RecycleGem(Gem * g);

	private:
	GemPool *		_gemPool;
	SDL_Surface *	_gemTexture;
};

