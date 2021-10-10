///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/ImageSheetsManager.h"

namespace gaia
{

void ImageSheetsManager::registerImageSheet(ImageSheet* is)
{
	if(is)
	{
		myImageSheets[is->getName()] = std::shared_ptr<ImageSheet>(is);
	}
	else
	{
		throw GuiException("Unable to register : ImageSheet is null");
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageSheetsManager::clearImages()
{
	myImageSheets.clear();
}

} //end namespace