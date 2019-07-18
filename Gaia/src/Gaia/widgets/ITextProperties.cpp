///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ITextProperties.h"
#include "Gaia/widgets/IText.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/GuiManager.h"

#include <sstream>

namespace gaia
{
namespace properties
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ITextSetTextColor::ITextSetTextColor(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ITextSetTextColor::setProperty(BaseWidget& target, const std::string& value)
{
	int r, g, b;
	std::istringstream stream(value);
	stream >> r >> g >> b;
	if(stream.fail())
	{
		ILogger::log(ILogger::ERRORS) << "Property : Cannot convert " 
										   << value << " into a color\n";
		return;
	}


	Color color(r, g, b);

	dynamic_cast<gaia::IText*>(&target)->setTextColor(color);
}

//Need font loader ?
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//TextSetFont::TextSetFont(const std::string& name)
//:Property(name)
//{
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextSetFont::setProperty(BaseWidget& target, const std::string& value)
//{
//	PtrFont font(new BaseFont(
//	dynamic_cast<gaia::Label*>(&target)->setFont();
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ITextSetFontSize::ITextSetFontSize(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ITextSetFontSize::setProperty(BaseWidget& target, const std::string& value)
{
	float size;
	std::istringstream stream(value);
	if(!(stream >> size))
	{
		ILogger::log(ILogger::ERRORS) << "Property : cannot convert " 
										   << value << "to font size\n";
		return;
	}

	float ratioY = GuiManager::getInstance()->getRatioY();

	dynamic_cast<gaia::IText*>(&target)->setFontSize(
								static_cast<unsigned int>(size * ratioY));
}


} //end namespace properties

} //end namespace
