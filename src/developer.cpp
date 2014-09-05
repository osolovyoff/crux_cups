#include "developer.h"

extern HGE* hge;

void DevelopClick(Image * img)   { if (img->IsHover()) system("start http://brainstorage.me/vbloodv"); }
void DeveloperHover(Image * img) { img->SetSecondViewMode(); }
void DeveloperLeave(Image * img) { img->SetDefaultMode();    }

void DeveloperScene::Initialize()
{
	developer.reset(new Image("vbv", 0, 0));
	developer->AddEventHandlerForClick(DevelopClick);
	developer->AddEventHandlerForHover(DeveloperHover);
	developer->AddEventHandlerForLeave(DeveloperLeave);
	to_menu_btn.reset(new ToMenuButton("quit",600,300));
}

int DeveloperScene::Update()
{
	developer->Update();
	return to_menu_btn->Update(DEVSCENE);
}

void DeveloperScene::Render()
{
	developer->Render();
	to_menu_btn->Render();
}

void DeveloperScene::Release()
{
	developer.reset();
	to_menu_btn.reset();
}



