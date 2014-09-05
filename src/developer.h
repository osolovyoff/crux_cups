#ifndef developer_h__
#define developer_h__

#include "scene.h"
#include "image.h"
#include "to_menu_btn.h"

class DeveloperScene: public IScene
{
private:
	virtual int	 Update();
	virtual void Initialize();
	virtual void Render();
	virtual void Release();

private:
	ImageShared        developer;
	ToMenuButtonShared to_menu_btn;
};

#endif // developer_h__