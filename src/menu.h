#ifndef menu_h__
#define menu_h__

#pragma once
#include <math.h>
#include "hge/hge.h"
#include "hge/hgegui.h"
#include "hge/hgefont.h"
#include "boost/shared_ptr.hpp"

#include "scene.h"
#include "menuitem.h"

typedef boost::shared_ptr<hgeFont> FontShared;
typedef boost::shared_ptr<hgeGUI>  UIMenuShared;

class Menu:public IScene
{
public:
		 Menu();
	void Initialize();
	void Render();
	int  Update();
	void Release();

private:
	hgeFont*     font;
	UIMenuShared menu;
	HEFFECT	     hover_sound;
};

typedef boost::shared_ptr<Menu> MenuShared;
typedef std::vector<UIMenuShared> MenuVector;

#endif // menu_h__
