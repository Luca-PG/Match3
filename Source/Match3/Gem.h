#pragma once
#include "SDL.h"
#include "GameConfig.h"
#include "GameGrid.h"
#include "SDLHelper.h"

class Gem : public IGridObject
{
public:
    Gem( int x, int y, int w, int h, SDL_Surface * texture );
	~Gem();

	virtual int		Type();
	virtual void	Match();
	virtual void	Move( vector2 * destination);

	//All gems point to the same texture, that contains multiple frames
	SDL_Surface * Texture;

	//Position and size of the gem
    SDL_Rect Bounds;

	//Render the gem
    void Show();

	//Change the gem type and the related rectangle to detect the right frame on the texture
	void SetType(GemType type);

	//Smoothly moves the gem on the screen
	void UpdateMovement(int elapsedTime);

private:
	bool			_isMoving;
	int				_moveElapsedTime;
	vector2			_startingPosition;
	vector2			_destinationOffset;
	GemType			_type;
    const SDL_Rect* _textureFrame;

};

