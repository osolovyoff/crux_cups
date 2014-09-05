#ifndef tutorial_h__
#define tutorial_h__

#include "scene.h"
#include "image.h"
#include "to_menu_btn.h"

class TutorialScene: public IScene
{
private:
	virtual int	 Update();
	virtual void Initialize();
	virtual void Render();
	virtual void Release();
private:
	WidgetShared tutorial;
	ToMenuButtonShared to_menu_btn;
};

#endif // tutorial_h__