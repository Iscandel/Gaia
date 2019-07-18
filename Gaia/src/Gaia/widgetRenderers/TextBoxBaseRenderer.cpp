///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/TextBoxBaseRenderer.h"

namespace gaia
{
TextBoxBaseRenderer::TextBoxBaseRenderer(PtrWidget w)
//:TplWidgetRenderer(w),
:TplTextWidgetRenderer(w)
,myTextOffsetX(0.f) 
{
	//myWidget->assignToModel(this);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxBaseRenderer::onAssignedToWidget(PtrWidget w)
{
	TplTextWidgetRenderer::onAssignedToWidget(w);

	//Be careful : onAssignedToWidget should be called in the base renderer class
	//after assignation of w to myWidget. Otherwise, myWidget will be NULL.
	myWidget->assignToModel(this);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int TextBoxBaseRenderer::computeCaretPosition(const Point& pos)
{
	//Rect<double> rectText = getTextArea();
	IntRect rectText = getTextArea();

	if(pos.x > rectText.x && pos.x < (rectText.x + rectText.width))
	{
		float totalPos = pos.x + myTextOffsetX;
		const std::string& text = myWidget->getText();
		PtrFont font = myWidget->getFont();

		for(unsigned int i = 1; i <= text.size(); i++)
		{
			if(totalPos < font->getTextWidth(text.substr(0, i), myWidget->getFontSize()))
				return i - 1;
		}

		return static_cast<int>(text.size());
	}

	return -1;
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//Rect<double> TextBoxBaseRenderer::getTextArea()
//{
//	const std::string areaName = "text";
//
//	Rect<double> rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
//	if(myAreas.find(areaName) != myAreas.end())
//	{
//		//rect = myAreas[areaName];
//
//		rect.x = myAreas[areaName].x * myWidget->getWidth();
//		rect.y = myAreas[areaName].y * myWidget->getHeight();
//
//		//if relative coords
//		//if(myAreas[areaName].width < 1.)
//			rect.width = myAreas[areaName].width * myWidget->getWidth();
//
//		//if(myAreas[areaName].height < 1.)
//			rect.height = myAreas[areaName].height * myWidget->getHeight();
//	}
//
//	return rect;
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxBaseRenderer::update(Observable*)
{
	const std::string& text = myWidget->getText();

	//Rect<double> rect = getTextArea();
	IntRect rect = getTextArea();
	//assert(rect.width >= 0 && "Negative TextBox width ??");
	if(rect.width < 0)
		return;

	PtrFont font = myWidget->getFont();

	float textWidth = font->getTextWidth(text, myWidget->getFontSize());

	if(textWidth <= rect.width)
	{
		myTextOffsetX = 0.f;
		myTextDisplayed = text;
		return;
	}

	int posCaret = myWidget->getCaretPosition();

	std::string textToCaret = text.substr(0, posCaret);

	float widthToCaret = font->getTextWidth(textToCaret, myWidget->getFontSize());

	if(widthToCaret - myTextOffsetX < 0)
	{
		myTextOffsetX -= myWidget->getWidth() / 2;//10.f;
		myTextOffsetX = myTextOffsetX < 0.f ? 0.f : myTextOffsetX;
	}
	else if(widthToCaret - myTextOffsetX > rect.width)
	{
		float shift = font->getTextWidth(text.substr(posCaret - 1, 1), myWidget->getFontSize());
		myTextOffsetX += shift; 
	}

	myTextDisplayed = text;
}


} //end namespace