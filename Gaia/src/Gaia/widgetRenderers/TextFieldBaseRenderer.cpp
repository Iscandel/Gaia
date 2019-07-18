///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/TextFieldBaseRenderer.h"
#include "Gaia/widgets/ScrollBar.h"

namespace gaia
{


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextFieldBaseRenderer::TextFieldBaseRenderer(PtrWidget w)
:TplTextWidgetRenderer<TextField>(w)
//,myMustDisplayCaret(false)
//,myElapsedTime(0.f)
,mySelectionColor(0, 0, 255)
,myBackgroundColor(200, 200, 200)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void TextFieldBaseRenderer::update(unsigned int elapsedTime)
//{	
//	myElapsedTime += elapsedTime;
//	if(myWidget->hasFocus() && ((int)(myElapsedTime * 2 / 1000.f) % 2 == 0) )
//	{
//		myMustDisplayCaret = true;
//	}
//	else
//	{
//		myMustDisplayCaret = false;
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int TextFieldBaseRenderer::computeCaretPosition(const Point& pos)
{
	//Rect<double> area = getTextArea();
	IntRect area = getTextArea();
	float value = myWidget->getScrollBarV()->getValue();
	const std::string& text = myWidget->getText();
	TextField::LineList list = myWidget->getFormattedText();
	PtrFont font = myWidget->getFont();

	if(text.size() == 0)
		return 0;

	int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- area.y) / myWidget->getFontSize());
	int firstDisplayedLine = static_cast<int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);

	//if(pos.x > zone.x && pos.x < (zone.x + zone.width))// && 
	   //pos.y > rectTexte.y && pos.y < (rectTexte.y + rectTexte.height))
	{
		int relLine = static_cast<int>((pos.y - area.y) / static_cast<float>(myWidget->getFontSize()));

		int numLine = std::min(relLine + firstDisplayedLine, (int)list.size() - 1);
		numLine = std::max(0, numLine);

		unsigned int endLinePos;
		if(numLine >= static_cast<int>(list.size() - 1))
		{
			endLinePos = (unsigned int)text.size();
		}
		else
		{
			endLinePos = list[numLine + 1].startPosition - 1;
		}

		
		for(unsigned int i = list[numLine].startPosition; i <= endLinePos; i++)
		{
			if(pos.x < area.x + font->getTextWidth(
				text.substr(list[numLine].startPosition, i - list[numLine].startPosition), 
				myWidget->getFontSize()))
				return i /*+ liste[relLine + firstDisplayedLine].startPosition*/ ;
		}

		return endLinePos;
	}
	
	return -1;
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int TextFieldBaseRenderer::computeCaretPosition(bool isNewLineSup)
{
	//Rect<double> area = getTextArea();
	IntRect area = getTextArea();

	TextField::LineList list = myWidget->getFormattedText();
	const std::string& text = myWidget->getText();
	PtrFont font = myWidget->getFont();
	unsigned int currentCaretPos = myWidget->getCaretPosition();

	size_t line = list.size() - 1; //List.size() is always > 0
	for(unsigned int i = 0; i < list.size(); i++)
	{
		if(list[i].startPosition > currentCaretPos)
		{
			line = i - 1;
			break;
		}
	}

	std::string lineToCaret = text.substr(list[line].startPosition, currentCaretPos - list[line].startPosition);
	float width = font->getTextWidth(lineToCaret, myWidget->getFontSize());

	if(isNewLineSup)
	{
		if(line == list.size() - 1)
			return currentCaretPos;

		line++;
	}
	else
	{
		if(line == 0)
			return currentCaretPos;

		line--;
	}

	for(unsigned int i = list[line].startPosition; i < list[line].startPosition + list[line].length; i++)
	{
		std::string lineToCaret = text.substr(list[line].startPosition, i - list[line].startPosition);
		float tmpWidth = font->getTextWidth(lineToCaret, myWidget->getFontSize());
		if(tmpWidth >= width)
			return i;
	}	

	return currentCaretPos;
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextFieldBaseRenderer::draw_impl(BaseGraphics* Gfx)
//{
//	if(myWidget->isOpaque())
//	{
//		drawBackground(Gfx);
//	}
//
//	drawSelection(Gfx);
//	drawCaret(Gfx);
//	drawText(Gfx);
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextFieldBaseRenderer::drawBackground(BaseGraphics* Gfx)
//{
//	//Rect<double> area = getTextArea();
//
//	Gfx->drawRectangle(Point(myWidget->getX(), myWidget->getY()), 
//					   myWidget->getWidth(),myWidget->getHeight(), 
//					   myBackgroundColor);
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextFieldBaseRenderer::drawSelection(BaseGraphics* Gfx)
//{
//	Rect<double> area = getTextArea();
//
//	int selectionStart = myWidget->getSelectionStart();
//	int selectionEnd = myWidget->getSelectionEnd();
//
//	if(selectionStart == selectionEnd)
//		return;
//
//	const std::string& text = myWidget->getText();
//	PtrFont font = myWidget->getFont();
//
//	float value = myWidget->getScrollBarV()->getValue();
//	int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- area.y) / myWidget->getFontSize());
//
//	TextField::LineList list = myWidget->getFormattedText();
//	unsigned int firstDisplayedLine = static_cast<unsigned int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);
//
//	unsigned int startLine = 0;
//	unsigned int endLine = list.size() - 1;
//
//	for(unsigned int i = firstDisplayedLine; i < list.size(); i++)
//	{
//		if(list[i].startPosition < selectionStart && list[i].startPosition + list[i].length >= selectionStart)
//			startLine = i;
//		if(list[i].startPosition < selectionEnd  && list[i].startPosition + list[i].length >= selectionEnd)
//		{
//			endLine = i;
//			break;
//		}
//	}
//
//	for(unsigned int i = startLine; i <= endLine; i++)
//	{
//		int widthStartToSel = 0; //n'a de sens que pour la première ligne
//		int widthEndSelToEndLine = 0; //n'a de sens que pour la dernière ligne
//
//		if(i == startLine)
//		{
//			widthStartToSel = 
//				font->getTextWidth(
//					text.substr(list[i].startPosition, selectionStart - list[i].startPosition), 
//					myWidget->getFontSize());
//		}
//
//		if(i == endLine)
//		{
//			int finTexte = (i == list.size() - 1) ? text.size() : list[i + 1].startPosition;
//			widthEndSelToEndLine = area.width - 
//				font->getTextWidth(
//					text.substr(list[i].startPosition, selectionEnd - list[i].startPosition),
//					myWidget->getFontSize());
//		}
//
//		Gfx->drawRectangle(
//			Point(myWidget->getX() + widthStartToSel + area.x, 
//				  myWidget->getY() + (i - firstDisplayedLine ) * myWidget->getFontSize())+ area.y,
//			area.width - widthStartToSel - widthEndSelToEndLine,
//			myWidget->getFontSize(),
//			mySelectionColor);
//	}
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextFieldBaseRenderer::drawCaret(BaseGraphics* Gfx)
//{
//	if(myMustDisplayCaret)
//	{
//		const std::string& text = myWidget->getText();
//		int caretPosition = myWidget->getCaretPosition();
//		PtrFont font = myWidget->getFont();
//		//float widthToCaret = myWidget->getFont()->getTextWidth(textToCaret, myWidget->getFontSize());
//		TextField::LineList liste = myWidget->getFormattedText();
//		float value = myWidget->getScrollBarV()->getValue();
//		//int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- zone.y) / myWidget->getFontSize());
//		float nbElementsDisplayArea = myWidget->getScrollBarV()->getVisibleAmount();
//		int firstDisplayedLine = static_cast<int>(value * (liste.size() - nbElementsDisplayArea) + 0.5f);
//
//		Rect<double> rect = getTextArea();
//		
//		int ligne = liste.size() - 1;
//		for(unsigned int i = 0; i < liste.size(); i++)
//		{
//			if(liste[i].startPosition > caretPosition)
//			{
//				ligne = i - 1;
//				break;
//			}
//		}
//
//		std::string lineToCaret;
//		if(ligne >= 0)
//			lineToCaret = text.substr(liste[ligne].startPosition, caretPosition - liste[ligne].startPosition);
//		float width = font->getTextWidth(lineToCaret, myWidget->getFontSize());
//		
//		int xAff = myWidget->getX() + static_cast<int>(rect.x);
//		int yAff = myWidget->getY() + static_cast<int>(rect.y);
//
//
//		Gfx->drawLine(
//			Point(xAff + width, yAff + myWidget->getFontSize() * (std::max(ligne, 0) - firstDisplayedLine)), 
//			Point(xAff + width, 
//				  yAff + myWidget->getFontSize() * (std::max(ligne, 0) - firstDisplayedLine) + myWidget->getFontSize()), 
//			myWidget->getTextColor());
//	}
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextFieldBaseRenderer::drawText(BaseGraphics* Gfx)
//{
//	Rect<double> area = getTextArea();
//	float value = myWidget->getScrollBarV()->getValue();
//	const std::string& text = myWidget->getText();
//	TextField::LineList list = myWidget->getFormattedText();
//	PtrFont font = myWidget->getFont();
//
//	//int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- zone.y) / myWidget->getFontSize());
//	int nbElementsDisplayArea = static_cast<int>((area.height) / myWidget->getFontSize());
//	int firstDisplayedLine = static_cast<int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);
//
//	int num = 0;
//	for(unsigned int i = firstDisplayedLine; i < list.size(); i++)
//	{
//		int endPos = i < list.size() - 1 ? list[i + 1].startPosition : text.size();
//		std::string displayedText = text.substr(list[i].startPosition, endPos - list[i].startPosition);
//		displayedText.erase(
//        std::remove_if( displayedText.begin(), displayedText.end(), supprRetourLignes() ),
//        displayedText.end() );
//		//std::string::iterator it = displayedText.begin();
//		//while(it != displayedText.end())
//		//{
//		//	if(*it == '\n' || *it == '\r\n')
//		//		it = displayedText.erase(it);
//		//	else
//		//		++it;
//		//}
//
//		Gfx->drawText(font, 
//			displayedText, 
//			myWidget->getX() + area.x, 
//			myWidget->getY() + num * myWidget->getFontSize() + area.y,
//			myWidget->getTextColor(), 
//			myWidget->getFontSize());
//
//		num++;
//	}
//}

//Rect<double> TextFieldBaseRenderer::getTextArea()
//{
//	//Rect<double> area(0, 0, myWidget->getWidth(), myWidget->getHeight());
//	const std::string areaName = "texte";
//
//	Rect<double> rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
//	if(myAreas.find(areaName) != myAreas.end())
//	{
//		rect = myAreas[areaName];
//
//		//Si coordonnées relatives
//		if(myAreas[areaName].x < 1.)
//			rect.x = myAreas[areaName].x * myWidget->getWidth();
//
//		//Si coordonnées relatives
//		if(myAreas[areaName].y < 1.)
//			rect.y = myAreas[areaName].y * myWidget->getHeight();
//
//		//Si coordonnées relatives
//		if(myAreas[areaName].width < 1.)
//			rect.width = myAreas[areaName].width * myWidget->getWidth();
//
//		if(myAreas[areaName].height < 1.)
//			rect.height = myAreas[areaName].height * myWidget->getHeight();
//	}
//
//	return rect;
//	//return area;
//}

} //end namespace