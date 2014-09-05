#include <string>
#include "hge/hgesprite.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<hgeSprite> SpriteShared;

class Cursor
{
public:
		 Cursor();
	void Render();

private:
	SpriteShared m_sprite;

};