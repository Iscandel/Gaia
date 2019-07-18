///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/VisualString.h"

namespace gaia
{
VisualString::VisualString(const Color& col, unsigned int height)
:myColor(col)
,mySize(height)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void VisualString::draw(BaseGraphics* Gfx, const std::string& text, int x, int y)
{
	myFont->drawText(Gfx, text, x, y, myColor, mySize);
}

} //end namespace