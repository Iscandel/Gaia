///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/TextFieldSimpleRenderer.h"
#include "Gaia/widgets/ScrollBar.h"

namespace gaia
{
struct checkNewLine
{
	bool operator() (char c)
	{
		return (c == '\n'); //|| c == '\r\n'); wrong
	}
};

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextFieldSimpleRenderer::TextFieldSimpleRenderer(PtrWidget w)
:TextFieldBaseRenderer(w)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextFieldSimpleRenderer::draw_impl(BaseGraphics* Gfx)
{
	if(myWidget->isOpaque())
	{
		drawBackground(Gfx);
	}

	drawSelection(Gfx);
	drawCaret(Gfx);
	drawText(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextFieldSimpleRenderer::drawBackground(BaseGraphics* Gfx)
{
	//Rect<double> area = getTextArea();

	Gfx->drawRectangle(Point(0,0),//myWidget->getX(), myWidget->getY()), 
		myWidget->getWidth(),myWidget->getHeight(), 
		myBackgroundColor);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextFieldSimpleRenderer::drawSelection(BaseGraphics* Gfx)
{
	//Rect<double> area = getTextArea();
	IntRect area = getTextArea();

	unsigned int selectionStart = myWidget->getSelectionStart();
	unsigned int selectionEnd = myWidget->getSelectionEnd();

	if(selectionStart == selectionEnd)
		return;

	const std::string& text = myWidget->getText();
	PtrFont font = myWidget->getFont();

	float value = myWidget->getScrollBarV()->getValue();
	int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- area.y) / myWidget->getFontSize());

	const TextField::LineList& list = myWidget->getFormattedText();
	unsigned int firstDisplayedLine = static_cast<unsigned int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);

	size_t startLine = 0;
	size_t endLine = list.size() - 1; //NB : list.size() is always >= 1

	for(size_t i = firstDisplayedLine; i < list.size(); i++)
	{
		if(list[i].startPosition < selectionStart && list[i].startPosition + list[i].length >= selectionStart)
			startLine = i;
		if(list[i].startPosition < selectionEnd  && list[i].startPosition + list[i].length >= selectionEnd)
		{
			endLine = i;
			break;
		}
	}

	for(size_t i = startLine; i <= endLine; i++)
	{
		int widthStartToSel = 0; //Only useful for the first line
		int widthEndSelToEndLine = 0; //Only useful for the last line

		if(i == startLine)
		{
			widthStartToSel = (int)
				font->getTextWidth(
				text.substr(list[i].startPosition, selectionStart - list[i].startPosition), 
				myWidget->getFontSize());
		}

		if(i == endLine)
		{
			//int endText = (i == list.size() - 1) ? text.size() : list[i + 1].startPosition;
			widthEndSelToEndLine = (int)(area.width - 
				font->getTextWidth(
				text.substr(list[i].startPosition, selectionEnd - list[i].startPosition),
				myWidget->getFontSize()));
		}

		Gfx->drawRectangle(
			Point((int)(/*myWidget->getX() +*/ widthStartToSel + area.x), 
			(int)(/*myWidget->getY() +*/ (i - firstDisplayedLine ) * myWidget->getFontSize()+ area.y)),
			(int)(area.width - widthStartToSel - widthEndSelToEndLine),
			myWidget->getFontSize(),
			mySelectionColor);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextFieldSimpleRenderer::drawCaret(BaseGraphics* Gfx)
{
	if(myMustDisplayCaret)
	{
		const std::string& text = myWidget->getText();
		unsigned int caretPosition = myWidget->getCaretPosition();
		PtrFont font = myWidget->getFont();
		unsigned int fontSize = myWidget->getFontSize();
		//float widthToCaret = myWidget->getFont()->getTextWidth(textToCaret, myWidget->getFontSize());
		const TextField::LineList& list = myWidget->getFormattedText();
		float value = myWidget->getScrollBarV()->getValue();
		//int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- zone.y) / myWidget->getFontSize());
		float nbElementsDisplayArea = myWidget->getScrollBarV()->getVisibleAmount();
		int firstDisplayedLine = static_cast<int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);

		//Rect<double> rect = getTextArea();
		IntRect rect = getTextArea();

		int ligne = (int)list.size() - 1;
		for(unsigned int i = 0; i < list.size(); i++)
		{
			if(list[i].startPosition > caretPosition)
			{
				ligne = i - 1; //could be < 0 
				break;
			}
		}

		std::string lineToCaret;
		if(ligne >= 0)
			lineToCaret = text.substr(list[ligne].startPosition, caretPosition - list[ligne].startPosition);

		float width = font->getTextWidth(lineToCaret, fontSize);

		int xAff = /*myWidget->getX() +*/ static_cast<int>(rect.x);
		int yAff = /*myWidget->getY() +*/ static_cast<int>(rect.y);

		Point first(static_cast<int>(xAff + width), 
					static_cast<int>(yAff + fontSize * (std::max(ligne, 0) - firstDisplayedLine)));
		Point last(static_cast<int>(xAff + width), 
				   static_cast<int>(yAff + fontSize * (std::max(ligne, 0) - firstDisplayedLine) + fontSize));

		Gfx->drawLine(first, last, myWidget->getTextColor());
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextFieldSimpleRenderer::drawText(BaseGraphics* Gfx)
{
	//Rect<double> area = getTextArea();
	IntRect area = getTextArea();
	float value = myWidget->getScrollBarV()->getValue();
	const std::string& text = myWidget->getText();
	const TextField::LineList& list = myWidget->getFormattedText();
	PtrFont font = myWidget->getFont();

	//int nbElementsDisplayArea = static_cast<int>((myWidget->getHeight()- zone.y) / myWidget->getFontSize());
	int nbElementsDisplayArea = static_cast<int>((area.height) / myWidget->getFontSize());
	int firstDisplayedLine = static_cast<int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);

	int num = 0;
	for(unsigned int i = firstDisplayedLine; i < list.size(); i++)
	{
		int endPos = i < list.size() - 1 ? list[i + 1].startPosition : text.size();
		std::string displayedText = text.substr(list[i].startPosition, endPos - list[i].startPosition);
		displayedText.erase(
			std::remove_if( displayedText.begin(), displayedText.end(), checkNewLine() ),
			displayedText.end() );
		//std::string::iterator it = displayedText.begin();
		//while(it != displayedText.end())
		//{
		//	if(*it == '\n' || *it == '\r\n')
		//		it = displayedText.erase(it);
		//	else
		//		++it;
		//}

		Gfx->drawText(font, 
			displayedText, 
			(int)(/*myWidget->getX() +*/ area.x), 
			(int)(/*myWidget->getY() +*/ num * myWidget->getFontSize() + area.y),
			myWidget->getTextColor(), 
			myWidget->getFontSize());

		num++;
	}
}

} //end namespace
