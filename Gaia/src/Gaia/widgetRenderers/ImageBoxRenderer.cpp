///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/ImageBoxRenderer.h"

namespace gaia
{
ImageBoxRenderer::ImageBoxRenderer(PtrWidget w)
:TplWidgetRenderer(w) 
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageBoxRenderer::draw_impl(BaseGraphics* Gfx)
{
	const std::string state = "normal";
	if(imageExists(state))
	{
		Gfx->drawImage(myImages[state], 
					   0,//myWidget->getX(),
					   0,//myWidget->getY(),
					   myWidget->getWidth(), 
					   myWidget->getHeight());
	}
}

} //end namespace