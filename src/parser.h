#ifndef resource_manager_h__
#define resource_manager_h__

#include <string>
#include <vector>
#include "boost/shared_ptr.hpp"
#include "tinyxml/tinyxml.h"


// SETTINGS.XML THIS IS KING AND GOD
// хороший стиль возвращать для всех return bool (получилось или нет)


typedef std::string String;
typedef std::vector<String> LevelList;

//int	         map   [cell_count_h][cell_count_w];

class ResourceManager
{
public: 
	void LoadLevelList(LevelList & level_list);
	void LoadLevel(String path,int *map, int *result, int size);
private:
} static parser;
 
#endif // resource_manager_h__