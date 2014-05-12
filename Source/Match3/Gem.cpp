#include "Gem.h"


Gem::Gem( int x, int y, int w, int h, SDL_Surface * texture )
{
    Texture = texture;

    Bounds.x = x;
    Bounds.y = y;
    Bounds.w = w;
    Bounds.h = h;

	IsMatching = false;
}

Gem::~Gem()
{
}

void Gem::Match()
{
	IsMatching = true;
}

void Gem::Move( vector2 * destination)
{
	_isMoving				= true;
	_moveElapsedTime		= 0;
    _startingPosition.x     = Bounds.x;
    _startingPosition.y     = Bounds.y;
    _destinationOffset.x	= destination->x - _startingPosition.x;
    _destinationOffset.y	= destination->y - _startingPosition.y;
}

int Gem::Type()
{
	return static_cast<int>(_type);
}

void Gem::SetType(GemType type)
{
	_type = type;

	switch(_type)
	{
		default:
		case Type_Blue	  : _textureFrame = &Rect_Gem_Blue	  ;	break;
		case Type_Green	  : _textureFrame = &Rect_Gem_Green	  ;	break;
		case Type_Purple  : _textureFrame = &Rect_Gem_Purple  ;	break;
		case Type_Red	  : _textureFrame = &Rect_Gem_Red	  ;	break;
		case Type_Yellow  : _textureFrame = &Rect_Gem_Yellow  ;	break;
	}

}

void Gem::UpdateMovement(int elapsedTime)
{
    if (_moveElapsedTime <= ANIMATION_TIME)
    {
        _moveElapsedTime += elapsedTime;
        if (_moveElapsedTime >= ANIMATION_TIME)
        {
            _moveElapsedTime = ANIMATION_TIME;
            _isMoving = false;
        }
        Bounds.x = _startingPosition.x + (_destinationOffset.x * (_moveElapsedTime / (float)ANIMATION_TIME));
        Bounds.y = _startingPosition.y + (_destinationOffset.y * (_moveElapsedTime / (float)ANIMATION_TIME));
    }
}

void Gem::Show()
{
    ApplySurface( Bounds.x, Bounds.y, Texture, Screen(), _textureFrame );
}