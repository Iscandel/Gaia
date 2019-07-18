///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/TextBoxSimpleRenderer.h"
//#include "Gaia/BaseFont.h"
#include "Gaia/Color.h"

namespace gaia
{
TextBoxSimpleRenderer::TextBoxSimpleRenderer(PtrWidget w)
:TextBoxBaseRenderer(w)
,myBackgroundColor(0, 0, 0)
,myEdgeColor1(167, 166, 170)
,myEdgeColor2(133, 135, 140)
,myEdgeColor3(220, 223, 228)
//,myElapsedTime(0.f)
//,myMustDisplayCaret(true)
{
	//myWidget->assignToModel(this);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxSimpleRenderer::draw_impl(BaseGraphics* Gfx)
{
	//Draw the background only if it is opaque
	if(myWidget->isOpaque())
	{
		drawBackground(Gfx);
	}

	drawSelection(Gfx);

	drawText(Gfx);

	//Draw the edge only if it is opaque
	if(myWidget->isOpaque())
	{
		drawEdge(Gfx);
	}

	drawCaret(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxSimpleRenderer::drawBackground(BaseGraphics* Gfx)
{
	Gfx->drawRectangle(
		Point(0,0),//myWidget->getX(), myWidget->getY()),
		Point(/*myWidget->getX() +*/ myWidget->getWidth(), /*myWidget->getY() +*/ myWidget->getHeight()),
		myBackgroundColor
	);
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxSimpleRenderer::drawText(BaseGraphics* Gfx)
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
void TextBoxSimpleRenderer::drawEdge(BaseGraphics* Gfx)//, int x, int y)
{
	//Horizontal, light grey
	Gfx->drawLine(Point(0,0),//myWidget->getX(), 
						//myWidget->getY()), 
				  Point(/*myWidget->getX() +*/ myWidget->getWidth(), 
						0),//myWidget->getY()),
				  myEdgeColor1
	);
	
	//Vertical, light grey
	Gfx->drawLine(Point(0,0),//myWidget->getX(), 
						//myWidget->getY()), 
				  Point(0,//myWidget->getX(), 
						/*myWidget->getY() +*/ myWidget->getHeight()),
				  myEdgeColor1
	);

	//Horizontal, dark grey
	Gfx->drawLine(Point(0,1),//myWidget->getX(), 
						//myWidget->getY() + 1), 
				  Point(/*myWidget->getX() +*/ myWidget->getWidth(),
						/*myWidget->getY() +*/ 1 ),
				  myEdgeColor2
	);

	//Vertical, dark grey
	Gfx->drawLine(Point(1,1),//myWidget->getX() + 1, 
						//myWidget->getY() + 1), 
				  Point(/*myWidget->getX() +*/ 1, 
						/*myWidget->getY() +*/ myWidget->getHeight()),
				  myEdgeColor2
	);

	//Horizontal, light
	Gfx->drawLine(Point(/*myWidget->getX() +*/ 1, 
						/*myWidget->getY() +*/ myWidget->getHeight()), 
				  Point(/*myWidget->getX() +*/ myWidget->getWidth(), 
						/*myWidget->getY() +*/ myWidget->getHeight()),
				  myEdgeColor3
	);

	//Vertical, light
	Gfx->drawLine(Point(/*myWidget->getX() +*/ myWidget->getWidth(), 
						/*myWidget->getY() +*/ 1), 
				  Point(/*myWidget->getX() +*/ myWidget->getWidth(), 
						/*myWidget->getY() +*/ myWidget->getHeight()),
				  myEdgeColor3
	);
}

//void TextBoxSimpleRenderer::update(unsigned int tempsEcoule)
//{	
//	myElapsedTime += tempsEcoule;
//	if(myWidget->hasFocus() && ((int)(myElapsedTime * 2 / 1000.f) % 2 == 0) )
//	{
//		myMustDisplayCaret = true;
//	}
//	else
//	{
//		myMustDisplayCaret = false;
//	}
//}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextBoxSimpleRenderer::update(Observable*)
//{
//	const std::string& text = myWidget->getText();
//
//	Rect<double> rect = getTextArea();
//
//	PtrFont font = myWidget->getFont();
//
//	float textWidth = font->getTextWidth(text, myWidget->getFontSize());
//
//	if(textWidth <= rect.width)
//	{
//		myTextOffsetX = 0.f;
//		myTextDisplayed = text;
//		return;
//	}
//
//	int posCaret = myWidget->getCaretPosition();
//
//	std::string textToCaret = text.substr(0, posCaret);
//
//	float widthToCaret = font->getTextWidth(textToCaret, myWidget->getFontSize());
//
//	if(widthToCaret - myTextOffsetX < 0)
//	{
//		myTextOffsetX -= myWidget->getWidth() / 2;//10.f;
//		myTextOffsetX = myTextOffsetX < 0.f ? 0.f : myTextOffsetX;
//	}
//	else if(widthToCaret - myTextOffsetX > rect.width)
//	{
//		float shift = font->getTextWidth(text.substr(posCaret - 1, 1), myWidget->getFontSize());
//		myTextOffsetX += shift; 
//	}
//
//	myTextDisplayed = text;
//
//}

//int TextBoxRendu::computeCaretPosition(const Point& pos)
//{
//	Rect<double> rectTexte = getTextArea();
//
//	if(pos.x > rectTexte.x && pos.x < (rectTexte.x + rectTexte.width))// && 
//	   //pos.y > rectTexte.y && pos.y < (rectTexte.y + rectTexte.height))
//	{
//		float posTotale = pos.x + myTextOffsetX;
//		const std::string& texte = myWidget->getText();
//		PtrFont fonte = myWidget->getFont();
//
//		for(unsigned int i = 1; i <= texte.size(); i++)
//		{
//			if(posTotale < fonte->getTextWidth(texte.substr(0, i), myWidget->getFontSize()))
//				return i - 1;
//		}
//
//		return texte.size();
//	}
//
//	return -1;
//}
//
//Rect<double> TextBoxRendu::getTextArea()
//{
//	const std::string nomZone = "texte";
//
//	Rect<double> rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
//	if(myAreas.find(nomZone) != myAreas.end())
//	{
//		rect = myAreas[nomZone];
//
//		//Si coordonnées relatives
//		if(myAreas[nomZone].width < 1.)
//			rect.width = myAreas[nomZone].width * myWidget->getWidth();
//
//		if(myAreas[nomZone].height < 1.)
//			rect.height = myAreas[nomZone].height * myWidget->getHeight();
//	}
//
//	return rect;
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextBoxSimpleRenderer::drawCaret(BaseGraphics* Gfx)
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
///////////////////////////////////////////////////////////////////////////////
void TextBoxSimpleRenderer::drawSelection(BaseGraphics* Gfx)
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