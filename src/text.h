#ifndef text_h__
#define text_h__

#include <string>
#include "hge/hge.h"
#include "hge/hgefont.h"
#include "boost/shared_ptr.hpp"

typedef boost::shared_ptr<hgeFont> FontShared;
typedef std::string String;

class Text
{
public:
	     Text(const float x, const float y);
	void Render() const;
	void SetCoords(const float x,const float y);
	void SetValue(String value);
private:
	FontShared m_font;
	String     m_value;
	float      m_x;
	float      m_y;
};

typedef boost::shared_ptr<Text> TextShared;

#endif // text_h__

