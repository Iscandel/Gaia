///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ComboBoxProperties.h"
#include "Gaia/widgets/ComboBox.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/tools/Tools.h"
#include "Gaia/GuiManager.h"

#include <sstream>

namespace gaia
{
namespace properties
{

ComboBoxSetText::ComboBoxSetText(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBoxSetText::setProperty(BaseWidget& target, const std::string& value)
{
	std::vector<std::string> vec = tools::split(value, "\n");
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		dynamic_cast<gaia::ComboBox*>(&target)->addItem(vec[i]);
	}
	
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ComboBoxSetTextColor::ComboBoxSetTextColor(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBoxSetTextColor::setProperty(BaseWidget& target, const std::string& value)
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

	dynamic_cast<gaia::ComboBox*>(&target)->setTextColor(color);
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
ComboBoxSetFontSize::ComboBoxSetFontSize(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBoxSetFontSize::setProperty(BaseWidget& target, const std::string& value)
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

	dynamic_cast<gaia::ComboBox*>(&target)->setFontSize(
								static_cast<unsigned int>(size * ratioY));
}

} //end namespace properties

} //end namespace
