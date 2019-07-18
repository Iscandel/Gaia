///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/RadioButtonImageRenderer.h"

namespace gaia
{
void RadioButtonImageRenderer::draw_impl(BaseGraphics* gfx)
{
	if(myWidget->isSelected())
	{
		gfx->drawImage(myImages["selected"], 0, 0, myWidget->getWidth(), myWidget->getHeight());
	}
	else
	{
		gfx->drawImage(myImages["unselected"], 0, 0, myWidget->getWidth(), myWidget->getHeight());
	}
}

} //end namespace