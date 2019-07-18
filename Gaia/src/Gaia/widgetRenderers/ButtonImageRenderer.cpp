#include "Gaia/widgetRenderers/ButtonImageRenderer.h"

namespace gaia
{
ButtonImageRenderer::ButtonImageRenderer(PtrWidget w)
:TplWidgetRenderer(w)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ButtonImageRenderer::draw_impl(BaseGraphics* Gfx)
{
	if(imageExists(myWidget->getStrWidgetState()))
	{
		Gfx->drawImage(myImages[myWidget->getStrWidgetState()], 
					   0,//myWidget->getX(),
					   0,//myWidget->getY(),
					   myWidget->getWidth(), 
					   myWidget->getHeight());
	}

	drawText(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ButtonImageRenderer::drawText(BaseGraphics* Gfx)
{
	Rect<double> textArea = getTextArea();
	PtrFont font = myWidget->getFont();
	const std::string& text = myWidget->getText();

	if(text == "")
		return;

	int posY = static_cast<int>(//myWidget->getY() 
									/*+*/ textArea.height / 2.
									- myWidget->getFontSize() / 2 //correct ???????????????????????????????????????
	);

	int textX = 0;
	int textY = posY;

	switch(myWidget->getTextAlignment())
	{
	case BaseWidget::LEFT:
		textX = static_cast<int>(/*myWidget->getX()*/ + textArea.x);
	break;

	case BaseWidget::CENTER:
		textX = static_cast<int>(
					//myWidget->getX() 
					/*+*/ textArea.width / 2.
					- font->getTextWidth(text, myWidget->getFontSize()) / 2.);

	break;

	case BaseWidget::RIGHT:
		textX = static_cast<int>(//myWidget->getX() 
								 /*+*/ textArea.width 
								 - font->getTextWidth(text, myWidget->getFontSize()));
	break;

	default:
		break;
	}	
	

	Gfx->drawText(font, text, textX, textY, myWidget->getTextColor(), myWidget->getFontSize());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Rect<double> ButtonImageRenderer::getTextArea()
{
	const std::string areaName = "text";

	Rect<double> rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
	if(myAreas.find(areaName) != myAreas.end())
	{
		//rect = myAreas[areaName];
		rect.x = myAreas[areaName].x * myWidget->getWidth();
		rect.y = myAreas[areaName].y * myWidget->getHeight();

		//If relative coordinates
		//if(myAreas[areaName].width < 1.)
			rect.width = myAreas[areaName].width * myWidget->getWidth();

		//if(myAreas[areaName].height < 1.)
			rect.height = myAreas[areaName].height * myWidget->getHeight();
	}

	return rect;
}

} //end namespace