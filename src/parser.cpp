#include "parser.h"


void ResourceManager::LoadLevelList( LevelList & level_list )
{
	TiXmlDocument file( "settings.xml" );

	if(file.LoadFile()) 
	{
		TiXmlElement * element = file.FirstChildElement("Settings");
		element = element->FirstChildElement("List");
		element = element->FirstChildElement("Level");
		while(element)
		{
			std::string path = element->Attribute("path");
			level_list.push_back(path);
			element = element->NextSiblingElement("Level");
		}
	}
}

void ResourceManager::LoadLevel(String path,int *map, int *result, int size)
{
	TiXmlDocument file( path.c_str() );
	if(file.LoadFile()) 
	{
		TiXmlElement * element = file.FirstChildElement("Level");
		element = element->FirstChildElement("Map");
		element = element->FirstChildElement("Cell");
		while (element)
		{
			int i,j,value;
			element->QueryIntAttribute("i",&i);
			element->QueryIntAttribute("j",&j);
			element->QueryIntAttribute("type",&value);
			(map+i*size)[j] = value;
			//map[i][j] = value;
			element = element->NextSiblingElement("Cell");
		}
		element = file.FirstChildElement("Level");
		element = element->FirstChildElement("Result");
		element = element->FirstChildElement("Cell");
		while (element)
		{
			int i,j,value;
			element->QueryIntAttribute("i",&i);
			element->QueryIntAttribute("j",&j);
			element->QueryIntAttribute("type",&value);
			(result+i*size)[j] = value;
			//result[i][j] = value;
			element = element->NextSiblingElement("Cell");
		}
	}
}


