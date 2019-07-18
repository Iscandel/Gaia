///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/ProgressBarSimpleRenderer.h"

namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ProgressBarSimpleRenderer::ProgressBarSimpleRenderer(PtrWidget target)
:TplWidgetRenderer<ProgressBar>(target)
,myBackgroundColor(150, 150, 150)
,myBarColor(0, 0, 255)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBarSimpleRenderer::draw_impl(BaseGraphics* Gfx)
{
	drawBackground(Gfx);
	drawBar(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBarSimpleRenderer::drawBackground(BaseGraphics* Gfx)
{
	Gfx->drawRectangle(Point(0,0),//myWidget->getX(),
							 //myWidget->getY()),
					   myWidget->getWidth(),
					   myWidget->getHeight(),
					   myBackgroundColor);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBarSimpleRenderer::drawBar(BaseGraphics* Gfx)
{
	Gfx->drawRectangle(Point(1,1),//myWidget->getX() + 1,
							 //myWidget->getY() + 1),
					   static_cast<int>(myWidget->getValue() * (myWidget->getWidth() - 2)),
					   myWidget->getHeight() - 2,
					   myBarColor);
}

} //end gaia
