///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/Button.h"
#include "Gaia/widgetRenderers/WidgetRenderer.h"

namespace gaia
{
//const std::string Button::myWidgetType = "Button";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Button::Button(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name, x, y, width, height)
,myTextAlignement(BaseWidget::CENTER)
{
	copyProperties<Button>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Button::Button(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myTextAlignement(BaseWidget::CENTER)
{
	copyProperties<Button>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Button::handleKeyPressed_impl(KeyboardEvent& ev)
{
	if(ev.getKey() == Keyboard::RETURN ||
		ev.getKey()== Keyboard::SPACE)
	{
		MouseEvent mouseEv(ev.getSource(), Event::MOUSE_RELEASED, -1, -1, 0, MouseButton::LEFT);
		onMouseReleased(mouseEv);
	}

	ev.use();

	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Button::setImages(const Image& normalIm, 
					   const Image& hoverIm,
					   const Image& clickIm)
{
	if(myRenderer)
	{
		//if normalIm's texture is null, we will delete the corresponding state
		myRenderer->addImage("normal", normalIm);

		if(hoverIm.getTexture() != NULL)
		{
			myRenderer->addImage("hover",hoverIm);
		}
		else
		{
			myRenderer->addImage("hover",normalIm);
		}

		if(clickIm.getTexture() != NULL)
		{
			myRenderer->addImage("click",clickIm);
		}
		else
		{
			myRenderer->addImage("click",normalIm);
		}

		invalidate();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Button::setTextAlignment(BaseWidget::HorizontalAlignment ha)
{
	myTextAlignement = ha;

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Button::onWidgetEntered()
{
	BaseWidget::onWidgetEntered();

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Button::onWidgetExited()
{
	BaseWidget::onWidgetExited();

	invalidate();
}

} //end namespace