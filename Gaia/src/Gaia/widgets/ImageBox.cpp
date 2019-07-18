///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ImageBox.h"
#include "Gaia/widgetRenderers/WidgetRenderer.h"

namespace gaia
{
//const std::string ImageBox::myWidgetType = "ImageBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ImageBox::ImageBox(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name, x, y, width, height)
{
	copyProperties<ImageBox>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ImageBox::ImageBox(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
{
	copyProperties<ImageBox>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageBox::setImage(const Image& image)
{
	monImage = image;

	if(myRenderer)
	{
		myRenderer->addImage("normal", image);
		invalidate();
	}
	else
	{
		ILogger::log(ILogger::ERRORS) << 
			"Cannot add image to ImageBox : No renderer set yet.\n";
	}
}

} //end namespace