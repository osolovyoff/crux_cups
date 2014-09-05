#include "game.h"
#include "utils.h"
#include "settings.h"


extern int	 screen_width;
extern int   screen_height;

extern HGE * hge;
extern hgeInputEvent event;

GameScene::GameScene():current_level(0)
{

}

void GameScene::Initialize()
{
	float mini_cell_size = (float) settings.GetMiniCell();
	float cell_size      = (float) settings.GetCell();
	float skip_space_h   = (float) settings.GetSkipH();
	float skip_space_w   = (float) settings.GetSkipW();

	// Set value of maps equal wall
	for (int i = 0; i < cell_count_h; i++)
		for (int j = 0; j < cell_count_w; j++)
			map[i][j] = result[i][j] = grid[i][j] = -1;

	// Get level data from XML
	parser.LoadLevelList(level_list);
	parser.LoadLevel(level_list[current_level], &map[0][0], &result[0][0], cell_count_w);
	
	// Filling containers
	for (int i = 0; i < cell_count_h; i++)
		for (int j = 0; j < cell_count_w; j++)
		{
			if ( map[i][j] == CELL_WALL )
			{
				widgets.push_back(WidgetShared(new Widget("wall", PosjToX(j), PosiToY(i), cell_size, cell_size)));
				widgets.push_back(WidgetShared(new Widget("wall", PosjToX(j,true), PosiToY(i,true), mini_cell_size, mini_cell_size)));
			}
			else
			{
				widgets.push_back(WidgetShared(new Widget("way", PosjToX(j), PosiToY(i), cell_size, cell_size)));
				widgets.push_back(WidgetShared(new Widget("way", PosjToX(j,true), PosiToY(i,true), mini_cell_size, mini_cell_size)));
			}
		}

		// initialize Button [Without order-field additions after all object of scene]
		for (int i = 0; i < cell_count_h; i++)
			for (int j = 0; j < cell_count_w; j++)
			{
				String btn("btn_" + IntToStr(map[i][j]));
				String rslt("mini_" + IntToStr(result[i][j]));

				if ( map[i][j] > 0 )	buttons.push_back(ButtonShared(new Button(btn, PosjToX(j), PosiToY(i), cell_size, cell_size)));
				if ( result[i][j] > 0 ) widgets.push_back(WidgetShared(new Widget(rslt, PosjToX(j,true), PosiToY(i,true), mini_cell_size, mini_cell_size)));
			}

	float text_pos_x = PosjToX(settings.GetCountW()+1,true);
	float text_pos_y = PosiToY(0,true);
	level_text.reset(new Text(text_pos_x, text_pos_y));
	level_text->SetValue("Level:"+IntToStr(current_level));

	text_pos_y = PosiToY(1,true);
	level_time.reset(new Text(text_pos_x, text_pos_y));
	timer = hge->Timer_GetTime();
	

}

int GameScene::Update()
{
	StorageUpdate(&widgets);
	StorageUpdate(&buttons);
	LogicOfLevel();
	level_time->SetValue("Time:"+IntToStr( static_cast<int>(hge->Timer_GetTime()-timer)));
	if ( hge->Input_GetKeyState(HGEK_ESCAPE)) return GAMEMENU;
	return GAMESCENE;
}

void GameScene::Render()
{
	StorageRender(&widgets);
	StorageRender(&buttons);
	level_text->Render();
	level_time->Render();
}

void GameScene::Release()
{
	images.clear();
	buttons.clear();
	widgets.clear();
}

bool GameScene::PathFinding( int ax, int ay, int bx, int by ) 
{
	way_list.clear();

	// Build Grid using by Map
	for (int i = 0; i < cell_count_h; i++)
		for (int j = 0; j < cell_count_w; j++)
		{
			if ( map[i][j] == CELL_BLANK ) grid[i][j] =  CELL_BLANK; else grid[i][j] = CELL_WALL;
		}

	// initialize first point in way
	int  dx[4] = {1, 0, -1, 0}; 
	int  dy[4] = {0, 1, 0, -1}; 
	int  d, x, y, k;
	bool IsStopped;
	int  len_way;  

	// wave moving
	d = 1;				
	grid[ay][ax] = 1;   
	do {
		IsStopped = true;               
		for ( y = 0; y < cell_count_h; ++y )
			for ( x = 0; x < cell_count_w; ++x )
				if ( grid[y][x] == d )                         
				{
					for ( k = 0; k < 4; ++k )                 
						if ( grid[y + dy[k]][x + dx[k]] == CELL_BLANK &&  y+dy[k]<cell_count_h && x+dx[k] < cell_count_w && y+dy[k]!=CELL_WALL && x+dx[k]!=CELL_WALL)
						{
							IsStopped = false;        
							grid[y + dy[k]][x + dx[k]] = d + 1;
						} 
				}
				d++;
	} while ( !IsStopped && grid[by][bx] == CELL_BLANK );

	if ( grid[by][bx] == CELL_BLANK || grid[by][bx] == CELL_WALL) return false;  // path not found

	// restore way
	len_way = grid[by][bx];              // length of way
	x = bx;
	y = by;
	d = len_way;
	while ( d > 0 )
	{ // надо пересмотреть случаи когда объект движется по краю матрицы
		way_list.push_back( Point2D(float(x), float(y)) );	// put first value of path
		d--;
		for (k = 0; k < 4; ++k)
			if (grid[y + dy[k]][x + dx[k]] == d && y+dy[k]<cell_count_h && x+dx[k] < cell_count_w && y+dy[k]!=-1 && x+dx[k]!=-1)
			{
				x = x + dx[k];
				y = y + dy[k];
				break; // GoTo cells equal d-1
			}
	}
	way_list.push_back(Point2D(float(ax), float(ay)));
	return true;
}

void GameScene::LogicOfLevel()
{
	int        count_pressed  =  0;
	int        count_hovered  =  0;
	static int count_first    = -1;
	static int count_second   = -1;

	for (ButtonVector::iterator i = buttons.begin(); i < buttons.end(); i++)
	{
		if ( (*i)->IsPress() ) 
		{
			int tmp_count = std::distance(buttons.begin(),i);
			if (tmp_count != count_first) count_second = tmp_count;
			count_pressed++;
		}
		if ( (*i)->IsHover() ) count_hovered++;
	}
	
	if ( event.type == INPUT_MBUTTONDOWN )
	{
		switch (count_pressed)
		{
		case 0:
			count_first = -1;
			break;
		case 1:
			if (count_hovered == 0)
			{
				float	ax,ay,bx,by;
				int		ai,aj,bi,bj;

				buttons.at(count_first)->GetPosition(&ax,&ay);
				hge->Input_GetMousePos(&bx,&by);
				
				ConvertCoordToPos(ax,ay,&ai,&aj);
				ConvertCoordToPos(bx,by,&bi,&bj);
				bool one_moved = OneButtonsIsMoved();
				if (!one_moved)
				{
					if ( PathFinding(ai,aj,bi,bj) )
					{
						int tmp = map[aj][ai]; 
						map[aj][ai] = map[bj][bi];
						map[bj][bi] = tmp;
						hge->Effect_PlayEx(hge->Effect_Load("data/move.wav"),6,0,1.0,false);

						for (WayList::reverse_iterator ri = way_list.rbegin(); ri != way_list.rend(); ++ri)
						{   // get coords use position
							int i = static_cast<int>( (*ri).x );
							int j = static_cast<int>( (*ri).y );
							float x,y;
							ConvertPosToCoord(&x, &y, i, j);
							// move widget
							buttons[count_first]->Move(x,y);

						}
						buttons[count_first]->SetUnPressed();
					}
					else
					{
						hge->Effect_PlayEx(hge->Effect_Load("data/beep.wav"),10,0,1.0,false);
					}
				}
			}
			else
			{
				count_first = count_second;
			}
			break;
		case 2:
			buttons.at(count_first)->SetUnPressed();
			count_first = count_second;
			break;
		}
	}

	CheckLevelCompleted();
}

template <class T>
void GameScene::StorageUpdate(T* storage)
{
	for (T::iterator i = storage->begin(); i < storage->end(); i++)
		(*i)->Update();
}

template <class T>
void GameScene::StorageRender(T* storage)
{
	for (T::iterator i = storage->begin(); i < storage->end(); i++)
		(*i)->Render();
}

void GameScene::CheckLevelCompleted()
{
	int all_cell_count = 0;
	int count_equal_cell = 0;
	
	
	if (!OneButtonsIsMoved())
	{
		for (int i = 0; i < cell_count_h; i++)
			for (int j = 0; j < cell_count_w; j++)
				if (map[i][j] > 0) all_cell_count++;

		for (int i = 0; i < cell_count_h; i++)
			for (int j = 0; j < cell_count_w; j++)
				if (result[i][j]==map[i][j] && map[i][j]>0) count_equal_cell++;

		if (count_equal_cell == all_cell_count)
		{
			Release();
			current_level++;
			Initialize();
		}
	}
	
	
}

inline bool GameScene::OneButtonsIsMoved()
{
	
	for (ButtonVector::iterator i = buttons.begin(); i < buttons.end(); i++) // Вынести в отдельную хуйню
		if ((*i)->IsMoved()) return true;

	return false;
}
