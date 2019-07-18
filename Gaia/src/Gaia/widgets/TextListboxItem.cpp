///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/TextListBoxItem.h"
#include "Gaia/widgets/ListBox.h"
#include "Gaia/BaseFont.h"

namespace gaia
{
TextListBoxItem::TextListBoxItem()
:mySelectionColor(102, 236, 216)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextListBoxItem::TextListBoxItem(const std::string& text,
								 const std::string& name, 
								 int x, 
								 int y, 
								 int width, 
								 int height)
:BaseListBoxItem(name, x, y, width, height)
,mySelectionColor(102, 236, 216)
,myText(text)
{
	setDimensions(0, 0, 0, 15);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextListBoxItem::drawItem(ListBox* widget, 
							   bool selected, 
							   BaseGraphics* Gfx, 
							   int x, 
							   int y)
{
	if(selected)
	{
		Gfx->drawRectangle(
			Point(x, y), 
			getWidth(), 
			getHeight(), 
			mySelectionColor);
	}

	Gfx->drawText(widget->getFont(), myText, x, y, widget->getTextColor(), widget->getFontSize());
}

}//end namespace