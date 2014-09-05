#include "cursor.h"
#include "tinyxml/tinyxml.h"
#include "utils.h"
extern HGE * hge;

Cursor::Cursor()
{
	GetSharedSpriteFromResource("cursor",&m_sprite);
}

void Cursor::Render()
{
	if (hge->Input_IsMouseOver())
	{	
		float x,y;
		hge->Input_GetMousePos(&x,&y);
		m_sprite->Render(x,y);
		hge->System_SetState(HGE_HIDEMOUSE, true);
	}
	else
	{
		hge->System_SetState(HGE_HIDEMOUSE, false);
	}
}
