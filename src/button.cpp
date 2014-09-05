#include "button.h"

extern HGE * hge;
extern hgeInputEvent event;

Button::Button( String id, float x, float y, float w, float h ):Widget(id,x,y,w,h),m_is_hover(false),m_is_press(false),m_is_moved(false)
{}

Button::Button( HTEXTURE tex, float ax, float ay, float bx, float by, float x, float y, float w, float h ):Widget(tex,ax,ay,bx,by,x,y,w,h),m_is_hover(false),m_is_press(false),m_is_moved(false)
{}

void Button::Update()
{
	switch (event.type)
	{
	case INPUT_MBUTTONDOWN:
		MouseButtonDownEventProcess();
		break;
	case INPUT_MOUSEMOVE:
		MouseMoveEventProcess();
		break;
	case INPUT_MBUTTONUP:
		MouseButtonUpEventProcess();
		break;
	}

	if ( !route.empty()) Run();
	else                 m_is_moved = false;
}

void Button::Move(float x, float y)
{
	m_is_moved = true;
	route.push_back(Point2D(x, y));
}

void Button::Run()
{
	const float SPEED = 500.0f;
	const float EPS = 10.5f;

	Point2D dir = route.front() - Point2D( GetX(), GetY() );

	bool IsFinishX = fabs( route.front().x - GetX() ) <= EPS;
	bool IsFinishY = fabs( route.front().y - GetY() ) <= EPS;

	if ( IsFinishX && IsFinishY )
	{
		SetX( route.front().x );
		SetY( route.front().y );
		route.pop_front();
	}
	else
	{
		dir.Normalize();
		float dt = hge->Timer_GetDelta();
		float x = GetX() + dir.x * SPEED * dt;
		float y = GetY() + dir.y * SPEED * dt;
		SetCoords(x,y);
	}
}

void Button::CheckHit()
{
	bool IsIntersectX = (GetX() < event.x) && (event.x < GetX() + GetW() );
	bool IsIntersectY = (GetY() < event.y) && (event.y < GetY() + GetH() );
	m_is_hover = (IsIntersectX && IsIntersectY);
}

void Button::SwitchBlendMode()
{
	if (m_is_press) SetSecondViewMode();
	else            SetDefaultMode();
}

void Button::GetPosition(float* x, float* y ) const
{
	*x = GetX();
	*y = GetY();
}

void Button::SetPressed()
{
	m_is_press = true;
	SetSecondViewMode();
}

void Button::SetUnPressed()
{
	m_is_press = false;
	SetDefaultMode();
}

void Button::MouseMoveEventProcess()
{
	CheckHit();
}

void Button::MouseButtonDownEventProcess()
{
	if (m_is_hover) 
	{
		m_is_press = true; 
		SetSecondViewMode();
	}
}

void Button::MouseButtonUpEventProcess(){}
bool Button::IsHover() const {return m_is_hover;}
bool Button::IsPress() const {return m_is_press;}
bool Button::IsMoved() const {return m_is_moved;}
