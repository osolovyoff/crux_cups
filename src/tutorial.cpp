#include "tutorial.h"
#include <Windows.h>
#include "utils.h"
#include "settings.h"

extern HGE* hge;

void TutorialScene::Initialize()
{
	const float default_w = 646;
	const float default_h = 384;
	
	const float screen_w = (float)settings.GetScreenWidth();
	const float screen_h = (float)settings.GetScreenHeight();
	
	float pos_x = (screen_w - default_w) / 2.f;
	float pos_y = (screen_h - default_h) / 2.f;

	tutorial.reset(new Widget("help", pos_x, pos_y-100, default_w, default_h));

	pos_x = (screen_w - 250) / 2.f;
	pos_y = pos_y + default_h;
	to_menu_btn.reset(new ToMenuButton("quit",pos_x,pos_y));
}

int TutorialScene::Update()
{
	tutorial->Update();
	return to_menu_btn->Update(TUTORIAL);
}

void TutorialScene::Render()
{
	tutorial->Render();
	to_menu_btn->Render();
}

void TutorialScene::Release()
{
	tutorial.reset();
	to_menu_btn.reset();
}



