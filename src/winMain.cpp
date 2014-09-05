#ifdef  DEBUG
//#include "vld/vld.h"
//#pragma comment(lib,"vld.lib") 
#endif // DEBUG

#ifndef WinMain_h__
#define WinMain_h__

#pragma comment(lib,"hge.lib")
#pragma comment(lib,"hgehelp.lib")

#include "boost/shared_ptr.hpp"
#include "hge/hge.h"

#include "manager.h"
#include "settings.h"

bool FrameFunc();
bool RenderFunc();

HGE* hge = 0;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	const char title[] = "ÑruxCaps";

	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_FPS, settings.GetFPS() );
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_TITLE, title);
	hge->System_SetState(HGE_HIDEMOUSE, true);
	hge->System_SetState(HGE_ZBUFFER,false);

	hge->System_SetState(HGE_WINDOWED, settings.IsWindowed() );
	hge->System_SetState(HGE_SCREENWIDTH,  settings.GetScreenWidth() );
	hge->System_SetState(HGE_SCREENHEIGHT, settings.GetScreenHeight() );

	if (hge->System_Initiate())
	{
		manager = new Manager();
		hge->System_Start();
	} 
	else
	{
		MessageBox(0, hge->System_GetErrorMessage(), "Error", MB_OK|MB_ICONERROR|MB_APPLMODAL);
	}
	manager->Release();
	delete manager;
	hge->System_Shutdown();
	hge->Release();
}

bool FrameFunc()
{
	return manager->Update();
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	manager->Render();
	hge->Gfx_EndScene();
	return false;
}


#endif // WinMain_h__
