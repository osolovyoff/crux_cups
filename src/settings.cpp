#include "settings.h"

Settings::Settings():is_windowed_mode(false), m_count_w(9), m_count_h(5)
{
	GetSettingsFromXML();
	CompareWorkRect();
}

void Settings::CompareWorkRect()
{
	m_screen_w = GetSystemMetrics(SM_CXSCREEN) / 100 * m_scale_w;
	m_screen_h = GetSystemMetrics(SM_CYSCREEN) / 100 * m_scale_h;

	if (m_screen_w > m_screen_h)
	{
		m_skip_w = (m_screen_w - m_screen_h) / 2;
		m_skip_h = 0;
		m_cell = m_screen_h / m_count_w;
	}
	else
	{
		m_skip_w = 0;
		m_skip_h = (m_screen_h - m_screen_w) / 2;
		m_cell = m_screen_h / m_count_w;
	}
	if (m_skip_h == 0)	m_skip_h = m_cell;
	if (m_skip_w == 0)	m_skip_w = m_cell;

	m_mini_cell = (m_screen_h - m_skip_h - m_count_h * m_cell) / ( m_count_h + 2 );
}

void Settings::GetSettingsFromXML()
{
	TiXmlDocument file("settings.xml");
	if(file.LoadFile()) 
	{
		TiXmlElement * element = file.FirstChildElement("Settings");

		element = element->FirstChildElement("Display");
		element->QueryBoolAttribute("is_window",&is_windowed_mode);

		if (is_windowed_mode)
		{
			element = element->FirstChildElement("Window");
			element->QueryIntAttribute("width",&m_scale_w);
			element->QueryIntAttribute("height",&m_scale_h);
			element->QueryIntAttribute("fps",&m_fps);
		}
		else
		{
			element = element->FirstChildElement("FullScreen");
			m_scale_h = 100;
			m_scale_w = 100;
			element->QueryIntAttribute("fps",&m_fps);
		}
	}
}

int  Settings::GetFPS() const{return m_fps;}
int  Settings::GetScreenWidth() const{return m_screen_w;}
int  Settings::GetScreenHeight() const{return m_screen_h;}
int  Settings::GetCell() const{return m_cell;}
int  Settings::GetMiniCell() const{return m_mini_cell;}
int  Settings::GetSkipW() const{return m_skip_w;}
int  Settings::GetSkipH() const{return m_skip_h;}
bool Settings::IsWindowed() const{return is_windowed_mode;}
int  Settings::GetCountW() const{return m_count_w;}
int  Settings::GetCountH() const{return m_count_h;}


