///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/TextProperties.h"
#include "Gaia/widgets/TextBox.h"
#include "Gaia/GuiManager.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/Color.h"

#include <sstream>

namespace gaia
{
namespace properties
{

TextSetText::TextSetText(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextSetText::setProperty(BaseWidget& target, const std::string& value)
{
	static_cast<gaia::BaseTextWidget*>(&target)->setText(value);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextSetTextColor::TextSetTextColor(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextSetTextColor::setProperty(BaseWidget& target, const std::string& value)
{
	int r, g, b;
	std::istringstream flux(value);
	flux >> r >> g >> b;
	if(flux.fail())
	{
		ILogger::log(ILogger::ERRORS) <<
			"Property : Text color " << value << " cannot be converted.\n";
		return;
	}

	Color color(r, g, b);

	static_cast<gaia::BaseTextWidget*>(&target)->setTextColor(color);
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
TextSetFont::TextSetFont(const std::string& name)
:Property(name)
{
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
void TextSetFont::setProperty(BaseWidget& target, const std::string& value)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextSetFontSize::TextSetFontSize(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextSetFontSize::setProperty(BaseWidget& target, const std::string& value)
{
	float size;
	std::istringstream stream(value);
	if(!(stream >> size))
	{
		ILogger::log(ILogger::ERRORS) <<
			"Property : Font size " << value << " cannot be converted.\n";
		return;
	}

	float ratioY = GuiManager::getInstance()->getRatioY();

	static_cast<gaia::BaseTextWidget*>(&target)->setFontSize(static_cast<unsigned int>(size * ratioY));
}

} //end namespace properties

} //end namespace
