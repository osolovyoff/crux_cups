#include "Manager.h"

extern HGE * hge;
hgeInputEvent event;

void Manager::Initialize()
{
	scenes.push_back(ISceneShared(new Menu()));           // GAMEMENU == 0
	scenes.push_back(ISceneShared(new GameScene()));      // GAMESCENE == 1
	scenes.push_back(ISceneShared(new TutorialScene()));  // TUTORIAL == 2
	scenes.push_back(ISceneShared(new DeveloperScene())); // DEVELOPER == 3
	scenes[m_current_scene]->Initialize();
	bg.reset(new Background());
	bg->Initialize();
	music = hge->Music_Load("data/main.it");
	hge->Music_Play(music,true,80,-1,-1); 
}

Manager::Manager():m_current_scene(0), m_next_scene(0)
{
	Initialize();		
}

bool Manager::Update()
{
	
	bg->Update();
	
	bool is_new_event = hge->Input_GetEvent(&event);
	if (!is_new_event) event.type = 0;

	m_next_scene = scenes[m_current_scene]->Update();	
	if (m_next_scene != m_current_scene)
	{
		if (m_next_scene == QUIT) return true;
		scenes[m_current_scene]->Release();
		scenes[m_next_scene]->Initialize();
		m_current_scene = m_next_scene;
	}
	return false;
	
}

void Manager::Render()
{
	if (m_current_scene <= 1) bg->Render();
	scenes[m_current_scene]->Render();
	m_cursor.Render();
}

void Manager::Release()
{
	hge->Music_Free(music);
	bg.reset();
}
