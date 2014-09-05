#ifndef level_h__
#define level_h__

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "tinyxml/tinyxml.h"

#include "image.h"
#include "button.h"
#include "scene.h"
#include "parser.h"
#include "utils.h"
#include "text.h"

static const int CELL_WALL  = -1;
static const int CELL_BLANK =  0;

static const int cell_count_w = 9;
static const int cell_count_h = 5;

typedef std::vector<String>	   LevelList;
typedef std::vector<Point2D>   WayList;

class GameScene: public IScene
{

public:
		 GameScene();
	void Initialize();
 	void Release();
	int  Update();
	void Render();

private:
	void LogicOfLevel();
	void CheckLevelCompleted();
	bool PathFinding(int ay, int ax, int by, int bx);
	bool OneButtonsIsMoved();

	template <class T>
	void StorageUpdate(T* storage);
	template <class T>
	void StorageRender(T* storage);

private:
	

	ImageVector  images;
	WidgetVector widgets;
	ButtonVector buttons;
	LevelList	 level_list;
	WayList      way_list;
	TextShared   level_text;
	TextShared   level_time;
	float        timer;
	int	         current_level;

	int map   [cell_count_h][cell_count_w];
	int grid  [cell_count_h][cell_count_w];
	int	result[cell_count_h][cell_count_w];
	
	
};

#endif // level_h__