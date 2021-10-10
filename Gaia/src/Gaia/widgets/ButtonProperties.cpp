///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/ImageSheetsManager.h"
#include "Gaia/widgets/ButtonProperties.h"
#include "Gaia/widgets/Button.h"
#include "Gaia/tools/Tools.h"
#include "Gaia/Image.h"

#include <assert.h>
#include <string>

namespace gaia
{
namespace properties
{
ButtonSetImages::ButtonSetImages(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ButtonSetImages::setProperty(BaseWidget& target, const std::string& value)
{
	std::vector<std::string> s = tools::split(value, "|");
	std::vector<std::string> sheets;
	std::vector<std::string> images;

	for(unsigned int i = 0; i < s.size(); i++)
	{
		std::vector<std::string> tmp = tools::split(s[i], "/");
		sheets.push_back(tmp[0]);
		images.push_back(tmp[1]);
	}

	assert(sheets.size() == images.size());

	Image& normal = *ImageSheetsManager::getInstance()->getImage(sheets[0], images[0]);
	Image& hover = *ImageSheetsManager::getInstance()->getImage(sheets[1], images[1]);
	Image& click = *ImageSheetsManager::getInstance()->getImage(sheets[2], images[2]);

	dynamic_cast<gaia::Button*>(&target)->setImages(normal, hover, click);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ButtonSetText::ButtonSetText(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ButtonSetText::setProperty(BaseWidget& target, const std::string& value)
{
	dynamic_cast<gaia::Button*>(&target)->setText(value);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ButtonSetTextAlignement::ButtonSetTextAlignement(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ButtonSetTextAlignement::setProperty(BaseWidget& target, const std::string& value)
{
	std::string s;
	for(unsigned int i = 0; i < value.size(); i++)
	{
		s += std::tolower(value[i]);
	}

	if(s == "center")
		dynamic_cast<gaia::Button*>(&target)->setTextAlignment(BaseWidget::CENTER);
	else if(s == "left")
		dynamic_cast<gaia::Button*>(&target)->setTextAlignment(BaseWidget::LEFT);
	else if(s == "right")
		dynamic_cast<gaia::Button*>(&target)->setTextAlignment(BaseWidget::RIGHT);
	else
	{
		ILogger::log(ILogger::ERRORS) << "Property : Cannot convert " 
										   << value << " into alignement\n";
	}
}

} //end namespace properties

} //end namespace
