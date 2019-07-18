///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/ProgressBarImageRenderer.h"

namespace gaia
{
ProgressBarImageRenderer::ProgressBarImageRenderer(PtrWidget w)
:TplWidgetRenderer(w)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBarImageRenderer::draw_impl(BaseGraphics* Gfx)
{
	drawBackground(Gfx);
	drawBar(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBarImageRenderer::drawBackground(BaseGraphics* Gfx)
{
	const std::string background = "background";
	if(imageExists(background))
	{
		Gfx->drawImage(myImages[background],
					   0,//myWidget->getX(),
					   0,//myWidget->getY(),
					   myWidget->getWidth(), 
					   myWidget->getHeight());
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBarImageRenderer::drawBar(BaseGraphics* Gfx)
{
	float value = myWidget->getValue();
	IntRect absCoords = myWidget->getScreenCoordinates();

	IntRect clippingRect(absCoords.x, 
						 absCoords.y, 
						 static_cast<int>(absCoords.x + value * myWidget->getWidth()),
						 absCoords.y + myWidget->getHeight());

	Gfx->pushClippingArea(clippingRect);

	const std::string bar = "bar";
	if(imageExists(bar))
	{
		Gfx->drawImage(myImages[bar], 
					   0,//myWidget->getX(),
					   0,//myWidget->getY(),
					   myWidget->getWidth(), 
					   myWidget->getHeight());
	}

	Gfx->popClippingArea();
}

} //end namespace