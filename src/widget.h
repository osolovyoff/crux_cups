#ifndef widget_h__
#define widget_h__

#include <vector>
#include <string>

#include "hge/hge.h"
#include "hge/hgesprite.h"

#include "tinyxml/tinyxml.h"
#include "boost/shared_ptr.hpp"

typedef std::string String;

class Widget
{
public:
				 Widget(String id, float x, float y);			 
				 Widget(String id, float x, float y, float w, float h );
				 Widget(HTEXTURE tex, float ax, float ay, float bx, float by, float x, float y, float w, float h );
	virtual		 ~Widget();

	virtual void Update();
	virtual void Render();
	void         ChangeTexture(HTEXTURE tex);
	void		 SetSecondViewMode();
	void	     SetDefaultMode();
	void         SetSize(float w, float h);
	void         SetCoords(float x, float y);
	void         SetX(float x);
	void         SetY(float y);
	float        GetX() const;
	float        GetY() const;
	float        GetW() const; // Get Width from widget
	float        GetH() const; // Get Height from widget
private:
	hgeSprite*   m_sprite;
	float        m_x, m_y;
	float        m_w, m_h;
};

typedef boost::shared_ptr<Widget> WidgetShared;
typedef std::vector<WidgetShared> WidgetVector;

#endif // widget_h__