#ifndef manager_h__
#define manager_h__

#include <string>
#include <vector>

#include "boost/shared_ptr.hpp"
#include "hge/hgesprite.h"

#include "parser.h"
#include "game.h"
#include "scene.h"
#include "menu.h"
#include "cursor.h"
#include "developer.h"
#include "tutorial.h"
#include "background.h"

typedef boost::shared_ptr<hgeSprite> SpriteShared;

class Manager
{
public:
		 Manager();
	void Initialize();
	bool Update();
	void Render();
	void Release();
private:
	int			     m_current_scene;
	int			     m_next_scene;
	Cursor           m_cursor;
	SceneVector	     scenes;
	BackgroundShared bg;
	HMUSIC           music;
} static *manager;

#endif // manager_h__