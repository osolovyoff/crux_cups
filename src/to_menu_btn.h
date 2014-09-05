#ifndef to_menu_btn_h__
#define to_menu_btn_h__

#include "boost/shared_ptr.hpp"

extern HGE * hge;

static bool exit_to_menu;
static void ReturnLeave(Image * img) { img->SetDefaultMode(); }
static void ReturnHover(Image * img) { img->SetSecondViewMode(); }
static void ReturnClick(Image * img) { if (img->IsHover()) exit_to_menu = true; }	

class ToMenuButton: public Image
{
public:
	ToMenuButton(String id, float x, float y):Image(id,x,y)
	{
		this->AddEventHandlerForHover(ReturnHover);
		this->AddEventHandlerForLeave(ReturnLeave);
		this->AddEventHandlerForClick(ReturnClick);
	};
	int Update(int current_game_state)
	{
		Image::Update();
		if ( hge->Input_GetKeyState(HGEK_ESCAPE)) exit_to_menu = true;
		if (exit_to_menu)
		{
			exit_to_menu = false;
			return 0;
		}
		return current_game_state;
	};
};

typedef boost::shared_ptr<ToMenuButton> ToMenuButtonShared;

#endif // to_menu_btn_h__

