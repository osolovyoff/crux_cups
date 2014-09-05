#include "menu.h"
#include "settings.h"

extern HGE * hge;

Menu::Menu()
{
	Initialize();
}

void Menu::Initialize()
{
	float screen_center_x = (float) settings.GetScreenWidth()/2;
	float screen_y = settings.GetScreenHeight()/3;
	hover_sound = hge->Effect_Load("data\\hover.wav");
	font = new hgeFont("data/Bernhard.fnt");
	menu.reset(new hgeGUI());
	menu->AddCtrl(new hgeGUIMenuItem(1,font,hover_sound,screen_center_x,screen_y+0*60.f,0.0f,"Start the game"));
	menu->AddCtrl(new hgeGUIMenuItem(2,font,hover_sound,screen_center_x,screen_y+1*60.f,0.1f,"How to play the game"));
	menu->AddCtrl(new hgeGUIMenuItem(3,font,hover_sound,screen_center_x,screen_y+2*60.f,0.2f,"Developer"));
	menu->AddCtrl(new hgeGUIMenuItem(4,font,hover_sound,screen_center_x,screen_y+3*60.f,0.4f,"Quit"));
	menu->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	menu->SetFocus(1);
	menu->Enter();
}

int Menu::Update()
{
	float dt = hge->Timer_GetDelta();
	return menu->Update(dt);
}

void Menu::Render()
{
	menu->Render();
}

void Menu::Release()
{
	hge->Effect_Free(hover_sound);
	menu->Leave();
	//delete font;
	//menu.reset();
	//font.reset();
}
