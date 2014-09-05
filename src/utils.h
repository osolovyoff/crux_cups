#ifndef utils_h__
#define utils_h__

#include <Shlwapi.h>
#include <Windows.h>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "Shlwapi.lib")
#include "hge/hgesprite.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<hgeSprite> SpriteShared;
typedef std::string String;


BOOL         IsFileExist(LPCSTR pszPath);
const String IntToStr(int number);

void		 GetSpriteFromResource(const String& id, hgeSprite * sprite);
void		 GetSharedSpriteFromResource(const String& id, SpriteShared * sprite);

void         ConvertCoordToPos(float  x, float  y, int* i, int* j);
void         ConvertPosToCoord(float* x, float* y, int  i, int  j);


float        PosjToX(const int& j, bool IsMiniCell = false);
float        PosiToY(const int& i, bool IsMiniCell = false);
int          CoorxToJ(const float& x, bool IsMiniCell = false);
int          CooryToI(const float& y, bool IsMiniCell = false);

void         Randomize();
int          Random(int from, int to);
float        fRandom(int from, int to);


#endif // utils_h__
