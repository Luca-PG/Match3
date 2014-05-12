#include "GemPool.h"

queue<Gem *> _hPool;

GemPool::GemPool(void)
{
}

GemPool::~GemPool(void)
{
	while(_hPool.size() >  0)
	{
		delete _hPool.front();
		_hPool.pop();
	}
}

Gem * GemPool::GetElement( GemType gemType )
{
	Gem * g = 0;
	if (_hPool.size() > 0)
	{
		g = _hPool.front();

		g->SetType(gemType);
		
		_hPool.pop();
	}
	return g;
}

void GemPool::Recycle( Gem * g )
{
	_hPool.push(g);
}
		