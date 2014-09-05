#ifndef button_h__
#define button_h__

#include <list>
#include <string>

#include "hge/hgevector.h"
#include "boost/shared_ptr.hpp"

#include "widget.h"

typedef hgeVector Point2D;
typedef std::list<Point2D> PointList;

class Button: public Widget
{
public:
	     Button(String id, float x, float y, float w, float h );
		 Button(HTEXTURE tex, float ax, float ay, float bx, float by, float x, float y, float w, float h);

	void Update();
	void Move(float x, float y);
	void Run();
	void CheckHit();
	void SwitchBlendMode();
	void SetPressed();
	void SetUnPressed();

	void GetPosition(float *x, float* y) const;
	bool IsHover() const;
	bool IsPress() const;
	bool IsMoved() const;

	virtual void MouseMoveEventProcess();
	virtual void MouseButtonDownEventProcess();
	virtual void MouseButtonUpEventProcess();

private:
	bool	  m_is_moved;
	bool      m_is_hover;
	bool	  m_is_press;
	PointList route;
};

typedef boost::shared_ptr<Button> ButtonShared;
typedef std::vector<ButtonShared> ButtonVector;

#endif // button_h__
