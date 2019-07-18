///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/Label.h"

#include "Gaia/tools/Logger.h"

namespace gaia
{
//const std::string Label::myWidgetType = "Label";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Label::Label(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name, x, y, width, height)
{
	copyProperties<Label>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Label::Label(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
{
	copyProperties<Label>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Label::Label(const std::string& name, 
			 const IntRect& dimensions, 
			 unsigned int fontSize, 
			 const Color& c, 
			 const std::string& text)
:BaseWidget(name, dimensions)
{
	copyProperties<Label>();

	setFontSize(fontSize);
	setTextColor(c);
	setText(text);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Label::setText(const std::string& text)
{
	myText = text;
	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Label::adjustSize()
{
	setDimensions(getX(),
				  getY(),
				  static_cast<int>(myFont->getTextWidth(myText, getFontSize())),
				  static_cast<int>(myFont->getTextHeight(myText, getFontSize())));//getFontSize()));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Label::adjustSize(int maxWidth)
{
	for(unsigned int i = 0; i < myText.size(); i++)
	{
		if(myFont->getTextWidth(myText.substr(0, i), getFontSize()) > maxWidth)
		{
			if(i == 1)
			{
				ILogger::log(ILogger::INFORMATIVE) << LOGPOSITION << 
					"Adjusting size of the text if too small\n";
				return;
			}
	
			myText.insert(myText.begin() + (i-1), '\n');
			i = 0;
		}
	}

	adjustSize();
}

} //end namespace