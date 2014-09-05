#include "utils.h"
#include "settings.h"
#include "tinyxml/tinyxml.h"

extern HGE * hge;

BOOL IsFileExist(LPCSTR pszPath)
{
	return PathFileExistsA(pszPath);
}

void ConvertCoordToPos( float x, float y, int* i, int* j )
{
	(*j) = static_cast<int>( (y - settings.GetSkipH() ) / settings.GetCell() );
	(*i) = static_cast<int>( (x - settings.GetSkipW() ) / settings.GetCell() );
}

void ConvertPosToCoord( float* x, float* y, int i, int j )
{
	(*y) = (float) settings.GetSkipH() + j*settings.GetCell();
	(*x) = (float) settings.GetSkipW() + i*settings.GetCell();
}

const String IntToStr(int number)
{
	std::ostringstream ostream;
	ostream << number;
	std::string str(ostream.str());
	return str;
}


float PosjToX( const int& j, bool IsMini)
{
	float cell;
	float skip_w;
	skip_w = static_cast<float>(settings.GetSkipW());

	if (IsMini)		cell = static_cast<float>(settings.GetMiniCell());
	else			cell = static_cast<float>(settings.GetCell());

	return skip_w + j*cell;
}

float PosiToY( const int& i, bool IsMini)
{
	float skip_h;
	float cell_count;

	skip_h =  static_cast<float>(settings.GetSkipH());
	cell_count = (float) settings.GetCountH();

	if (IsMini)
	{
		float cell = settings.GetCell();
		float mini_cell = settings.GetMiniCell();
		return skip_h + (cell * cell_count)+(i+1)*mini_cell;
	}
	else
	{
		float cell = static_cast<float>(settings.GetCell());
		return skip_h + i*cell;
	}
}

int CoorxToJ( const float& x, bool IsMini)
{
	int cell;
	int skip_w = settings.GetSkipW();
	int value = static_cast<int>(x);

	if (IsMini)	cell = settings.GetMiniCell();
	else		cell = settings.GetCell();

	return (value - skip_w) / cell;
}

int CooryToI( const float& y, bool IsMini)
{
	float skip_h;
	float cell_count;
	skip_h =  static_cast<float>(settings.GetSkipH());
	cell_count = (float) settings.GetCountH();
	int value = static_cast<float>(y);	

	if (IsMini)
	{
		float cell = settings.GetCell();
		float mini_cell = settings.GetMiniCell();
		return (value - skip_h - cell*cell_count)-1;
	}
	else
	{
		float cell = static_cast<float>(settings.GetCell());
		return ( value - skip_h ) / cell;
	}
}

void GetSpriteFromResource( const String& id, hgeSprite * sprite )
{
	TiXmlDocument file( "settings.xml" );
	if (file.LoadFile())
	{
		TiXmlElement * element = file.FirstChildElement("Resources");
		element = element->FirstChildElement("Sprite");
		while(element)
		{
			String attr = element->Attribute("id");

			if ( id == attr )
			{
				float spr_x, spr_y, spr_w, spr_h;
				String path;
				element->QueryStringAttribute("src",&path);
				element->QueryFloatAttribute("x",&spr_x);
				element->QueryFloatAttribute("y",&spr_y);
				element->QueryFloatAttribute("w",&spr_w);
				element->QueryFloatAttribute("h",&spr_h);
				sprite = new hgeSprite(hge->Texture_Load(path.c_str()), spr_x, spr_y, spr_w, spr_h);
				break;
			}
			else
			{
				element = element->NextSiblingElement("Sprite");
			}
		}
	}
}

void GetSharedSpriteFromResource( const String& id, SpriteShared * sprite )
{
	TiXmlDocument file( "settings.xml" );
	if (file.LoadFile())
	{
		TiXmlElement * element = file.FirstChildElement("Resources");
		element = element->FirstChildElement("Sprite");
		while(element)
		{
			String attr = element->Attribute("id");

			if ( id == attr )
			{
				float spr_x, spr_y, spr_w, spr_h;
				String path;
				element->QueryStringAttribute("src",&path);
				element->QueryFloatAttribute("x",&spr_x);
				element->QueryFloatAttribute("y",&spr_y);
				element->QueryFloatAttribute("w",&spr_w);
				element->QueryFloatAttribute("h",&spr_h);
				sprite->reset(new hgeSprite(hge->Texture_Load(path.c_str()), spr_x, spr_y, spr_w, spr_h));
				break;
			}
			else
			{
				element = element->NextSiblingElement("Sprite");
			}
		}
	}
}



void Randomize()
{
	srand(time(NULL));
}

int Random(const int from,const int to)
{
	if (!to)
	{
		int tmp = to;
		int rnd = rand()+from;
		return rnd;
	}
	else
	{
		return rand()%to+from;
	}
	
}

float fRandom(int from,int to)
{
	from *= 100.f;
	to   *= 100.f;
	float result;
	if ( !from || !to ) result = (from + to)/2;
	else			  result = rand()%to+from;
	return  result / 100.f;
}






