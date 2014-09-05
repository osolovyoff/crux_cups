#ifndef image_h__
#define image_h__

#include <string>

#include "hge/hgevector.h"
#include "boost/shared_ptr.hpp"

#include "widget.h"

class Image: public Widget
{
public:
		  Image(String id, float x, float y);
	      Image(String id, float x, float y, float w, float h );
		  Image(HTEXTURE tex, float ax, float ay, float bx, float by, float x, float y, float w, float h);

	void  Update();

	void  CheckHit();
	void  GetPosition(float* x, float* y) const;
	bool  IsHover() const;
	bool  IsClick() const;
	
	void AddEventHandlerForHover( void (*fn)(Image *img) );
	void AddEventHandlerForLeave( void (*fn)(Image *img) );
	void AddEventHandlerForClick( void (*fn)(Image *img) );

private:
	void  (*Click)(Image *img);
	void  (*Hover)(Image *img);
	void  (*Leave)(Image *img);

	bool m_is_hover;
	bool m_is_click;
};

typedef boost::shared_ptr<Image> ImageShared;
typedef std::vector<ImageShared> ImageVector;

#endif // image_h__
