///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/LabelRenderer.h"

namespace gaia
{
LabelRenderer::LabelRenderer(PtrWidget widget)
:TplWidgetRenderer<Label>(widget)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LabelRenderer::draw_impl(BaseGraphics* Gfx)
{
	const std::string& text = myWidget->getText();
	PtrFont font = myWidget->getFont();

	Gfx->drawText(font, 
		text, 
		0,//myWidget->getX(), 
		0,//myWidget->getY(), 
		myWidget->getTextColor(), 
		myWidget->getFontSize());
}

}