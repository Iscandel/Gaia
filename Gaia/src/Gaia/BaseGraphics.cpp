///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/BaseGraphics.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
BaseGraphics::BaseGraphics(void)
:myOptimizeDrawing(false)
,myInvalidate(true)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::pushClippingArea(const gaia::IntRect& area)
{
	if(myOldSizes.size() == 0)
	{
		myOldSizes.push(myWindowSize);
	}
	else
	{
		myOldSizes.push(myCurrentSize);
	}
	myCurrentSize = area;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::popClippingArea()
{
	if(myOldSizes.size() != 0)
	{
		myCurrentSize = myOldSizes.top();
		myOldSizes.pop();
	}
	else
	{
		myCurrentSize = myWindowSize;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::setOrigin(int x, int y)
{
	myOrigin.x = x; 
	myOrigin.y = y;
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::translate(int x, int y) 
{
	myOrigin.x += x; 
	myOrigin.y += y;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::assignWindowSize(int width, int height)
{
	myWindowSize.x = myWindowSize.y = 0;
	myWindowSize.height = height;
	myWindowSize.width = width;

	onWindowSizeAssigned();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::setGlobalFont(PtrFont font) 
{
	myGlobalFont = font; 
	BaseFont::setDefaultFont(font);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::drawText(VisualString& chaine, const std::string& texte, int x, int y)
{
	chaine.draw(this, texte, myOrigin.x + x, myOrigin.y + y);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::drawText(PtrFont font, 
							   const std::string& text, 
							   int x, 
							   int y, 
							   const Color& col, 
							   unsigned int charHeight)
{
	if(text == "")
		return;

	font->drawText(this, text, myOrigin.x + x, myOrigin.y + y, col, charHeight);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseGraphics::drawRectangle(const Point& topLeft, 
								 const Point& bottomRight, 
								 const Color& col, 
								 int outlineThickness,
								 const Color& outlineColor)
{
	drawRectangle(topLeft, 
				  bottomRight.x - topLeft.x, 
				  bottomRight.y - topLeft.y, 
				  col, 
				  outlineThickness, 
				  outlineColor
	);
}

void BaseGraphics::drawOptimized() 
{
	throw GuiException("Optimized drawing not implemented");
}

} //end namespace