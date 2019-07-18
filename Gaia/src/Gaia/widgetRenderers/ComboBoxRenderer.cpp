#include "Gaia/widgetRenderers/ComboBoxRenderer.h"
#include "Gaia/widgets/TextBox.h"

namespace gaia
{
ComboBoxRenderer::ComboBoxRenderer(PtrWidget w) 
:TplWidgetRenderer<ComboBox>(w) 
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBoxRenderer::draw_impl(BaseGraphics*)
{
	myWidget->getTextBox()->setFont(myWidget->getFont());
	myWidget->getTextBox()->setTextColor(myWidget->getTextColor());
	myWidget->getTextBox()->setFontSize(myWidget->getFontSize());

	myWidget->getListBox()->setFont(myWidget->getFont());
	myWidget->getListBox()->setTextColor(myWidget->getTextColor());
	myWidget->getListBox()->setFontSize(myWidget->getFontSize());
}

} //end namespace