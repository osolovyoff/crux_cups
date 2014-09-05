#include "image.h"
#include "hge/hgecolor.h"

extern HGE * hge;
extern hgeInputEvent event;


Image::Image( String id, float x, float y):Widget(id,x,y),Click(0),Hover(0),Leave(0)
{}

Image::Image( String id, float x, float y, float w, float h ):Widget(id,x,y,w,h),Click(0),Hover(0),Leave(0)
{}
				 
Image::Image(HTEXTURE tex, float ax, float ay, float bx, float by, float x, float y, float w, float h):Widget(tex,ax,ay,bx,by,x,y,w,h),Click(0),Hover(0),Leave(0)
{}

void Image::Update()
{
	switch (event.type)
	{
	case INPUT_MOUSEMOVE:
		CheckHit();	
		if ( Hover && m_is_hover )  Hover(this);
		if ( Leave && !m_is_hover ) Leave(this);
		break;
	case INPUT_MBUTTONDOWN:
		if ( Click && m_is_click )  Click(this);
		break;
	}
}

void Image::CheckHit()
{
	bool IsIntersectX = (GetX() < event.x) && (event.x < GetX() + GetW() );
	bool IsIntersectY = (GetY() < event.y) && (event.y < GetY() + GetH() );
	m_is_hover = (IsIntersectX && IsIntersectY);	
}

void Image::GetPosition( float* x, float* y ) const
{
	*x = GetX();
	*y = GetY();
}

bool Image::IsHover() const
{
	return m_is_hover;
}

bool Image::IsClick() const
{
	return m_is_click;
}

void Image::AddEventHandlerForClick( void (*fn)(Image *img) )
{
	Click = fn;
}

void Image::AddEventHandlerForLeave( void (*fn)(Image *img) )
{
	Leave = fn;
}

void Image::AddEventHandlerForHover( void (*fn)(Image *img) )
{
	Hover = fn;
}