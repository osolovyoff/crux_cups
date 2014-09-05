#include "widget.h"

extern HGE * hge;
extern hgeInputEvent event;

Widget::Widget( String id, float x, float y )
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
				m_sprite = new hgeSprite(hge->Texture_Load(path.c_str()), spr_x, spr_y, spr_w, spr_h);
				m_x = x;
				m_y = y;
				m_w = spr_w;
				m_h = spr_h;
				break;
			}
			else
			{
				element = element->NextSiblingElement("Sprite");
			}
		}
	}
}


Widget::Widget( String id ,float x, float y, float w, float h )
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
				m_sprite = new hgeSprite(hge->Texture_Load(path.c_str()), spr_x, spr_y, spr_w, spr_h);
				m_x = x;
				m_y = y;
				m_w = w;
				m_h = h;
				break;
			}
			else
			{
				element = element->NextSiblingElement("Sprite");
			}
		}
	}
}

Widget::Widget( HTEXTURE tex, float ax, float ay, float bx, float by, float x, float y, float w, float h )
{
	m_sprite = new hgeSprite(tex,ax,ay,bx,by);
	m_x = x;
	m_y = y;
	m_w = w;
	m_h = h;
}

Widget::~Widget()
{
	delete m_sprite;
}

void Widget::Render()
{
	m_sprite->RenderStretch( m_x, m_y, m_x + m_w, m_y + m_h );
}

void Widget::Update()
{/*Empty*/}

void Widget::SetSecondViewMode()
{
	m_sprite->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	m_sprite->SetColor(0xCC111111);
}

void Widget::SetDefaultMode()
{
	m_sprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHABLEND | BLEND_NOZWRITE);
	m_sprite->SetColor(0xFFFFFFFF);
}

void Widget::SetSize( float w, float h )
{
	m_w = w;
	m_h = h;
}

void Widget::SetCoords( float x, float y )
{
	m_x = x;
	m_y = y;
}

void Widget::SetX( float x )
{
	m_x = x;
}

void Widget::SetY( float y )
{
	m_y = y;
}

float Widget::GetX() const
{
	return m_x;
}

float Widget::GetY() const
{
	return m_y;
}

float Widget::GetW() const
{
	return m_w;
}

float Widget::GetH() const
{
	return m_h;
}

void Widget::ChangeTexture(HTEXTURE tex)
{
	m_sprite->SetTexture(tex);

}

