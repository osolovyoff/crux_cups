#ifndef settings_h__
#define settings_h__

#include <Windows.h>
#include <string>
#include "tinyxml/tinyxml.h"

typedef std::string String;

class Settings
{
public:
		 Settings();
	int  GetScreenWidth() const;
	int  GetScreenHeight() const;
	int  GetFPS() const;
	int  GetCell() const;
	int  GetMiniCell() const;
	int  GetSkipW() const;
	int  GetSkipH() const;
	bool IsWindowed() const;
	int  GetCountW() const;
	int  GetCountH() const;

private:
	void GetSettingsFromXML();
	void CompareWorkRect();

private:
		  bool is_windowed_mode; 
	      int  m_screen_w; 
		  int  m_screen_h; 
		  int  m_scale_w; 
		  int  m_scale_h; 
		  int  m_fps; 
		  int  m_skip_w; 
		  int  m_skip_h; 
		  int  m_cell; 
 		  int  m_mini_cell; 
	const int  m_count_w;
	const int  m_count_h;


}static  settings; 

#endif // settings_h__
