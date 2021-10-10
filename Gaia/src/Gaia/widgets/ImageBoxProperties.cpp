///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/ImageSheetsManager.h"
#include "Gaia/widgets/ImageBoxProperties.h"
#include "Gaia/widgets/ImageBox.h"
#include "Gaia/tools/Logger.h"
#include "Gaia/tools/Tools.h"

#include <assert.h>
#include <vector>

namespace gaia
{
namespace properties
{
ImageBoxSetImage::ImageBoxSetImage(const std::string& name)
:Property(name)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageBoxSetImage::setProperty(BaseWidget& target, const std::string& value)
{
	std::vector<std::string> s = tools::split(value, "|");

	assert(s.size() >= 2);
	
	//Sheet name, image name
	Image& image = *ImageSheetsManager::getInstance()->getImage(s[0], s[1]);

	dynamic_cast<gaia::ImageBox*>(&target)->setImage(image);
}

} //end namespace properties

} //end namespace