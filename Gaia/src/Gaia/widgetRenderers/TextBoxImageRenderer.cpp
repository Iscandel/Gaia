#include "Gaia/widgetRenderers/TextBoxImageRenderer.h"
#include "Gaia/Color.h"

namespace gaia
{
TextBoxImageRenderer::TextBoxImageRenderer(PtrWidget w)
:TextBoxBaseRenderer(w)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxImageRenderer::draw_impl(BaseGraphics* Gfx)
{
	//Draw the background only if it is opaque
	if(myWidget->isOpaque())
	{
		drawBackground(Gfx);
	}

	drawSelection(Gfx);

	drawText(Gfx);

	drawCaret(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxImageRenderer::drawBackground(BaseGraphics* Gfx)
{
	if(imageExists(myWidget->getStrWidgetState()))
	{
		Gfx->drawImage(myImages[myWidget->getStrWidgetState()], 
					   0,//myWidget->getX(),
					   0,//myWidget->getY(),
					   myWidget->getWidth(), 
					   myWidget->getHeight()
		);
	}
					
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxImageRenderer::drawText(BaseGraphics* Gfx)
{
	IntRect rect = getTextArea();
	//Rect<double> rect = getTextArea();
	
	int xDisp = /*myWidget->getX() +*/ static_cast<int>(rect.x);
	int yDisp = /*myWidget->getY() +*/ static_cast<int>(rect.y);

	Gfx->drawText(myWidget->getFont(), 
				  myTextDisplayed, 
				  static_cast<int>(xDisp- myTextOffsetX), 
				  yDisp, 
				  myWidget->getTextColor(), 
				  myWidget->getFontSize()); 
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxImageRenderer::drawCaret(BaseGraphics* Gfx)
{
	if(myMustDisplayCaret)
	{
		const std::string& text = myWidget->getText();
		int posCaret = myWidget->getCaretPosition();
		std::string textToCaret = text.substr(0, posCaret);
		float widthToCaret = myWidget->getFont()->getTextWidth(textToCaret, myWidget->getFontSize());

		//Rect<double> rect = getTextArea();
		IntRect rect = getTextArea();
		
		int xDisp = /*myWidget->getX() +*/ static_cast<int>(rect.x);
		int yDisp = /*myWidget->getY() +*/ static_cast<int>(rect.y);


		Gfx->drawLine(
			Point(static_cast<int>(xDisp + widthToCaret - myTextOffsetX), yDisp), 
			Point(static_cast<int>(xDisp + widthToCaret - myTextOffsetX), static_cast<int>(yDisp + rect.height)),
			myWidget->getTextColor());
	}
}

//=============================================================================
/////////////////////////////////////////////////////////////////////////////
void TextBoxImageRenderer::drawSelection(BaseGraphics* Gfx)
{
	int selectionStart = myWidget->getSelectionStart();
	int selectionEnd = myWidget->getSelectionEnd();

	if(selectionEnd == selectionStart)
		return;

	int posCaret = myWidget->getCaretPosition();
	const std::string& text = myWidget->getText();
	std::string textToCaret = text.substr(0, posCaret);
	float widthToCaret = myWidget->getFont()->getTextWidth(textToCaret, myWidget->getFontSize());

	//Rect<double> rect = getTextArea();
	IntRect rect = getTextArea();
		
	int xAff = /*myWidget->getX() +*/ static_cast<int>(rect.x);
	int yAff = /*myWidget->getY() +*/ static_cast<int>(rect.y);

	float widthToSelectionEdge;
	if(selectionStart == posCaret) //Use getSelectionStart() et getSelectionEnd() instead
	{
		std::string textToSelectionEdge = text.substr(0, selectionEnd);
		widthToSelectionEdge = myWidget->getFont()->getTextWidth(textToSelectionEdge, myWidget->getFontSize());

	}
	else
	{
		std::string textToSelectionEdge = text.substr(0, selectionStart);
		widthToSelectionEdge = myWidget->getFont()->getTextWidth(textToSelectionEdge, myWidget->getFontSize());
	}

	float widthToSelectionStart = std::min(widthToSelectionEdge, widthToCaret);
	float widthToSelectionEnd = std::max(widthToSelectionEdge, widthToCaret);
	float selectionWidth = widthToSelectionEnd  - widthToSelectionStart;

	Gfx->drawRectangle(
		Point(static_cast<int>(xAff + widthToSelectionStart - myTextOffsetX), yAff),
		Point(static_cast<int>(xAff + widthToSelectionStart + selectionWidth - myTextOffsetX), static_cast<int>(yAff + rect.height)),
		Color(0, 0, 255));
}

} //end namespace
