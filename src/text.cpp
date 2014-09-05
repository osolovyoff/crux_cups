#include "text.h"

Text::Text(const float x, const float y) : m_value("empty"), m_x(x), m_y(y)
{
	m_font.reset(new hgeFont("data/Bernhard.fnt"));
	m_font->SetColor(ARGB(150,255,255,255));
	m_font->SetScale(1.f);
	m_font->SetZ(0);
}

void Text::Render() const
{
	m_font->printf(m_x,m_y,HGETEXT_LEFT,m_value.c_str());
}

void Text::SetCoords( const float x,const float y )
{
	m_x = x;
	m_y = y;
}

void Text::SetValue( String value )
{
	m_value = value;
}
