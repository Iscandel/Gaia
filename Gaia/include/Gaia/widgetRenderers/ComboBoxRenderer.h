#ifndef H__COMBOBOXRENDERER_010320122331
#define H__COMBOBOXRENDERER_010320122331

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/WidgetRenderer.h"
#include "Gaia/widgets/ComboBox.h"

namespace gaia
{
class ComboBoxRenderer :
	public gaia::TplWidgetRenderer<ComboBox>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// \param widget : A pointer to the widget owning the renderer.
	///////////////////////////////////////////////////////////////////////////
	ComboBoxRenderer(PtrWidget w = PtrWidget());

	///////////////////////////////////////////////////////////////////////////
	/// \brief Draws the widget. 
	///
	/// Should be overriden by derived class to perform the drawing.
	///
	/// \param Gfx : Pointer the graphics engine.
	///////////////////////////////////////////////////////////////////////////
	virtual void draw_impl(BaseGraphics* Gfx);
};

} //end namespace

#endif