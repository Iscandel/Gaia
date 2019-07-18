///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/WindowSimpleRenderer.h"

namespace gaia
{
TitleBarSimpleRenderer::TitleBarSimpleRenderer(PtrWidget widget)
:TplWidgetRenderer(widget)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TitleBarSimpleRenderer::draw_impl(BaseGraphics* Gfx)
{
	Gfx->drawRectangle(Point(myWidget->getX(), myWidget->getY()), myWidget->getWidth(), myWidget->getHeight(), Color(0, 0, 250));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
WindowSimpleRenderer::WindowSimpleRenderer(PtrWidget widget)
:TplWidgetRenderer(widget)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WindowSimpleRenderer::draw_impl(BaseGraphics* Gfx)
{
	Gfx->drawRectangle(Point(0,0),/*myWidget->getX(), myWidget->getY()), */myWidget->getWidth(), myWidget->getHeight(), Color(100, 200, 150));
}

} //end namespace