#ifndef background_h__
#define background_h__

#include "hge/hge.h"
#include "hge/hgesprite.h"
#include "boost/shared_ptr.hpp"


typedef boost::shared_ptr<hgeSprite> SpriteShared;

class Background
{
public:
		 ~Background();
	void Release();
	void Initialize();
	void Render();
	void Update();
private:
	hgeSprite* m_sprite;
	float      x;
	float      y;
	float      dx;
	float      dy;

};

typedef boost::shared_ptr<Background> BackgroundShared;

#endif // background_h__