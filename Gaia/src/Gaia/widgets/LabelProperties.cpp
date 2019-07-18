///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/LabelProperties.h"
#include "Gaia/widgets/Label.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/GuiManager.h"

#include <sstream>

namespace gaia
{
namespace properties
{

LabelSetText::LabelSetText(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LabelSetText::setProperty(BaseWidget& target, const std::string& value)
{
	dynamic_cast<gaia::Label*>(&target)->setText(value);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LabelSetTextColor::LabelSetTextColor(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LabelSetTextColor::setProperty(BaseWidget& target, const std::string& value)
{
	int r, g, b;
	std::istringstream flux(value);
	flux >> r >> g >> b;
	if(flux.fail())
	{
		ILogger::log(ILogger::ERRORS) << "Property : Cannot convert " 
										   << value << " into a color\n";
		return;
	}


	Color color(r, g, b);

	dynamic_cast<gaia::Label*>(&target)->setTextColor(color);
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
LabelSetFontSize::LabelSetFontSize(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LabelSetFontSize::setProperty(BaseWidget& target, const std::string& value)
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

	dynamic_cast<gaia::Label*>(&target)->setFontSize(
								static_cast<unsigned int>(size * ratioY));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LabelAdjustSize::LabelAdjustSize(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LabelAdjustSize::setProperty(BaseWidget& target, const std::string& value)
{
	float size;
	std::istringstream stream(value);
	if(!(stream >> size))
	{
		ILogger::log(ILogger::ERRORS) << "Property : Cannot convert " << value 
									<< " to float to adjust Label size\n";
		return;
	}

	double ratioX = GuiManager::getInstance()->getRatioX();

	if(size < 0.01) //size ~= 0
		dynamic_cast<gaia::Label*>(&target)->adjustSize();
	else
		dynamic_cast<gaia::Label*>(&target)->adjustSize((int)(size * ratioX));
}

} //end namespace properties

} //end namespace
