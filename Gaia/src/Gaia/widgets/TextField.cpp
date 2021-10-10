///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
//#include "Gaia/widgets/ProprietesTextField.h"
#include "Gaia/widgets/TextField.h"
#include "Gaia/widgets/ScrollBar.h"
#include "Gaia/tools/Binder.h"
#include "Gaia/tools/Tools.h"
//#include "Gaia/widgetRenderers/TextFieldRendu.h"
#include "Gaia/widgetRenderers/TextWidgetBaseRenderer.h"

#include <cmath>

namespace gaia
{
//const std::string TextField::myWidgetType = "TextField";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextField::TextField(const std::string& name, int x, int y, int width, int height)
:BaseTextWidget(name, x, y, width, height)
,PREFIX_SCROLLBARV("_VerticalScrollBar")
,PREFIX_SCROLLBARH("_HorizontalScrollBar")
{
	copyProperties<TextField>();
	getScrollBarV();
	
	//MaScrollBar->souscrireValeurScrollChange(std::bind(&TextField::valeurScrollAChange, this, _1));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TextField::TextField(const std::string& name, const IntRect& dimensions)
:BaseTextWidget(name, dimensions)
,PREFIX_SCROLLBARV("_VerticalScrollBar")
,PREFIX_SCROLLBARH("_HorizontalScrollBar")
{
	copyProperties<TextField>();
	getScrollBarV();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrScrollBar TextField::getScrollBarV()
{
	const std::string name = PREFIX_SCROLLBARV + getName();

	if(!isChildPresent(name))
	{
		createChild("ScrollBar", name);
	}

	return getChild<gaia::ScrollBar>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrScrollBar TextField::getScrollBarH()
{
	const std::string name = PREFIX_SCROLLBARH + getName();

	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}

	return getChild<gaia::ScrollBar>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::configureFormattedText()
{
	if(myFormattedText.size() == 0)
		return;

	unsigned int textSize = static_cast<unsigned int>(getText().size());

	if(myFormattedText.size() > 1)
	{
		for(unsigned int i = 0; i < myFormattedText.size() - 1; i++)
		{
			myFormattedText[i].length = myFormattedText[i + 1].startPosition - myFormattedText[i].startPosition;
		}

		myFormattedText.back().length = textSize - myFormattedText.back().startPosition;
	}
	else
	{
		myFormattedText[0].length = textSize;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
unsigned int TextField::firstModifiedLine(unsigned int insertionPos)
{
	assert(myFormattedText.size() > 0);

	bool isExceeded = false;
	unsigned int vectorPos = static_cast<unsigned int>(myFormattedText.size()) - 1;

	//Look for the first line modified by text insertion
	for(unsigned int i = 0; i < myFormattedText.size(); i++)
	{
		if(isExceeded)
		{
			if(insertionPos < myFormattedText[i].startPosition)
			{
				vectorPos = i - 1;
				break;
			}
		}
		else
		{
			if(insertionPos >= myFormattedText[i].startPosition)
			{
				isExceeded = true;
			}
		}
	}

	return vectorPos;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
	//On recherche la position du premier \n qui suit l'insertion de texte 
	//(si il existe). La ligne le précédant sera notre dernière ligne à modifier 
	//(sinon, on va jusqu'à la fin)
unsigned int TextField::lookForFirstNewLine(unsigned int pos, 
											unsigned int firstModifLine, 
											size_t textSize)
{
	//To avoid initialization problems with newLineListIndex
	assert(myFormattedText.size() > 0);

	size_t newLinePos = myText.find_first_of("\r\n", pos + textSize + 1); //+1 or not ??????????
	unsigned int newLineListIndex = ((unsigned int)myFormattedText.size()) - 1;

	for(unsigned int i = firstModifLine; i < myFormattedText.size(); i++)
	{
		if(myFormattedText[i].startPosition  + textSize > newLinePos)
		{
			newLineListIndex = i - 1;
			break;
		}
	}

	return newLineListIndex;
}

void TextField::modifyLineListStartPos(unsigned int min, int amount)
{
	//On modifie les lignes après le théorique \n, dont la pos de début est 
	//incrémentée de la taille du texte à ajouter
	for(unsigned int i = min; i < myFormattedText.size(); i++)
	{
		myFormattedText[i].startPosition += amount;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::reconstructSomeFormattedText(unsigned int firstModifLine, 
											 unsigned int newLineListIndex, 
											 int amount, 
											 const IntRect& textArea)
											 //const Rect<double>& textArea)
{
	//Construction of a temporary string for tests, to configure the new line list
	std::string textToModify;
	unsigned int startPosToModify = myFormattedText[firstModifLine].startPosition;

	//If there was only 1 line before the text insertion
	if(myFormattedText.size() == 1)
	{
		textToModify = myText;
	}
	else 
	{
		//If we have to consider text up to end
		if(newLineListIndex == myFormattedText.size() - 1)
		{
			textToModify = myText.substr(startPosToModify, myText.size());

		}
		else
		{
			//Remove -1 for the \n which must not been included
			int amountToModify = 
				myFormattedText[newLineListIndex].startPosition -  startPosToModify + 
				myFormattedText[newLineListIndex].length + amount - 1;

			textToModify = myText.substr(startPosToModify, amountToModify); 
		}

		//Delete obsolete lines, from the one following the first modified, 
		//till the end or the line before the first \n
		for(unsigned int i = firstModifLine + 1; i <= newLineListIndex /*- 1*/; i++)
		{
			myFormattedText.erase(myFormattedText.begin() + (firstModifLine + 1));
		}
	}

	std::string textTest;
	int numberInsertions = 0;
	//int debut = myFormattedText[firstModifLine].startPosition;

	unsigned int lastInsertion = 0;
	for(unsigned int i = 0; i < textToModify.size(); i++)
	{
		textTest += textToModify[i];

		if(textToModify[i] == '\n' ||textToModify[i] == '\r\n')
		{
			FormattedText format;
			format.startPosition = startPosToModify + i + 1;//i + pos;
		
			myFormattedText.insert(myFormattedText.begin() + firstModifLine + numberInsertions + 1, format);
			numberInsertions++;
			textTest = "";
			//myNewLineList.push_back(debut + i);
			//retrier = true;

			//On revient un caractère en arrière, ie, celui qui a dépassé
			//i--;
		}
		else
		{
			//texteTest += textToModify[i];

			if(getFont()->getTextWidth(textTest, getFontSize()) > textArea.width)
			{
				//Prevent insertions for too small widths
				if(i == lastInsertion)
				{
					myText = myText.substr(0, myText.size() - amount);
					return;
				}
				else
					lastInsertion = i;

				FormattedText format;
				format.startPosition = startPosToModify + i;//i + pos;

				myFormattedText.insert(myFormattedText.begin() + firstModifLine + numberInsertions + 1, format);
				numberInsertions++;
				textTest = "";

				//Come back 1 char back, ie, the one which exceeded
				i--;
			}
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::appendText(const std::string& text)
{
	insertText(text, static_cast<unsigned int>(myText.size()));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::insertText(const std::string& text, unsigned int pos)
{
	if(text == "")
		return;
	
	if(pos > myText.size())
	{
		throw GuiException("Text cannot be insert at position " 
			+ tools::numToString(pos) + " (invalid) for the widget" + getName());
		return;
	}

	//Initializes structure if necessary
	if(myFormattedText.size() == 0)//myText.size() == 0)
	{
		FormattedText format;
		format.startPosition = 0;
		
		myFormattedText.push_back(format);
	}

	//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	IntRect textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();

	//Insert text..
	myText.insert(pos, text);

	//bool aDepasse = false;
	//int posVecteur = myFormattedText.size() - 1;

	//Search for the first line that will be modified by text insertion
	int firstModifLine = firstModifiedLine(pos);

	////La recherche de la première ligne  qui sera modifiée par l'ajout de texte
	//for(unsigned int i = 0; i < myFormattedText.size(); i++)
	//{
	//	if(aDepasse)
	//	{
	//		if(pos < myFormattedText[i].startPosition)
	//		{
	//			posVecteur = i - 1;
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		if(pos >= myFormattedText[i].startPosition)
	//		{
	//			aDepasse = true;
	//		}
	//	}
	//}

	//Look for the first \n (if exists) after inserted text. The line before
	//it will be the last line to modify. Otherwise, we modify till the end.
	unsigned int newLineListIndex = lookForFirstNewLine(pos, firstModifLine, text.size());

	////On recherche la position du premier \n qui suit l'insertion de texte 
	////(si il existe). La ligne le précédant sera notre dernière ligne à modifier 
	////(sinon, on va jusqu'à la fin)
	//size_t posNouvelleLigne = myText.find_first_of("\r\n", pos + texte.size() + 1); //+1 ou pas ??????????
	//int posNouvelleLigneVecteur = myFormattedText.size() - 1;

	//for(int i = firstModifLine; i < myFormattedText.size(); i++)
	//{
	//	if(myFormattedText[i].startPosition  + texte.size() > posNouvelleLigne)
	//	{
	//		posNouvelleLigneVecteur = i - 1;
	//		break;
	//	}
	//}

	//We modify lines after the \n (if exists), and increment their start position
	//with inserted text size
	modifyLineListStartPos(newLineListIndex + 1, (int)text.size());

	////On modifie les lignes après le théorique \n, dont la pos de début est 
	////incrémentée de la taille du texte à ajouter
	//for(int i = newLineListIndex + 1; i < myFormattedText.size(); i++)
	//{
	//	myFormattedText[i].startPosition += texte.size();
	//}

	reconstructSomeFormattedText(firstModifLine, 
								 newLineListIndex, 
								 static_cast<int>(text.size()),
								 textArea);

	////Construction of a temporary string for tests, to configure the new line list
	//std::string textToModify;
	//unsigned int startPosToModify = myFormattedText[firstModifLine].startPosition;

	////If there was only 1 line before the text insertion
	//if(myFormattedText.size() == 1)
	//{
	//	textToModify = myText;
	//}
	//else 
	//{
	//	//If we have to consider text up to end
	//	if(newLineListIndex == myFormattedText.size() - 1)
	//	{
	//		textToModify = myText.substr(startPosToModify, myText.size());

	//	}
	//	else
	//	{
	//		//Remove -1 for the \n which must not been included
	//		int amountToModify = 
	//			myFormattedText[newLineListIndex].startPosition -  startPosToModify + 
	//			myFormattedText[newLineListIndex].length + text.size() - 1;

	//		textToModify = myText.substr(startPosToModify, amountToModify); 
	//	}

	//	//Delete obsolete lines, from the one following the first modified, 
	//	//till the end or the line before the first \n
	//	for(unsigned int i = firstModifLine + 1; i <= newLineListIndex /*- 1*/; i++)
	//	{
	//		myFormattedText.erase(myFormattedText.begin() + (firstModifLine + 1));
	//	}
	//}

	//std::string textTest;
	//int numberInsertions = 0;
	////int debut = myFormattedText[firstModifLine].startPosition;

	////Penser à virer le \n
	////Penser au cas où le texte à ajouter contient un \n. La recherche du prochain \n ne sera alors pas correcte
	//for(unsigned int i = 0; i < textToModify.size(); i++)
	//{
	//	textTest += textToModify[i];

	//	if(textToModify[i] == '\n' ||textToModify[i] == '\r\n')
	//	{
	//		FormattedText format;
	//		format.startPosition = startPosToModify + i + 1;//i + pos;
	//	
	//		myFormattedText.insert(myFormattedText.begin() + firstModifLine + numberInsertions + 1, format);
	//		numberInsertions++;
	//		textTest = "";
	//		//myNewLineList.push_back(debut + i);
	//		//retrier = true;

	//		//On revient un caractère en arrière, ie, celui qui a dépassé
	//		//i--;
	//	}
	//	else
	//	{
	//		//texteTest += textToModify[i];

	//		if(getFont()->getTextWidth(textTest, getFontSize()) > textArea.width)
	//		{

	//			FormattedText format;
	//			format.startPosition = startPosToModify + i;//i + pos;

	//			myFormattedText.insert(myFormattedText.begin() + firstModifLine + numberInsertions + 1, format);
	//			numberInsertions++;
	//			textTest = "";

	//			//On revient un caractère en arrière, ie, celui qui a dépassé
	//			i--;
	//		}
	//	}
	//}

	myCaret += static_cast<unsigned int>(text.size());
	adjustCaret();
	configureFormattedText();
	configureScrollBars();
	resetSelection();

	onTextChanged();

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::deleteTextRange(unsigned int startPosition, unsigned int endPosition)
{
	replaceText("", startPosition, endPosition - startPosition);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::deleteText(unsigned int startPosition, unsigned int amount)
{
	replaceText("", startPosition, amount);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::replaceTextRange(const std::string& text, unsigned int startPosition, unsigned int endPosition)
{
	if(startPosition > endPosition)
		throw GuiException("Start position must be lesser than end positon");

	replaceText(text, startPosition, endPosition - startPosition);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::replaceText(const std::string& text, unsigned int startPosition, unsigned int amount)
{
	unsigned int endPos = startPosition + amount;

	if(endPos > myText.size())
	{
		throw GuiException("Cannot replace more text than the text size : " 
			+ tools::numToString(endPos) + " > " + tools::numToString((int)myText.size()));
	}

	//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	IntRect textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();

	//bool aDepasse = false;

	//NB : myFormattedText.size() is always > 0
	//unsigned int posVecteur = (unsigned int)myFormattedText.size() - 1; 

	//Search for the first line that will be modified by text insertion
	unsigned int firstModifLine = firstModifiedLine(startPosition);

	//Look for the first \n (if exists) after inserted text. The line before
	//it will be the last line to modify. Otherwise, we modify till the end.
	unsigned int newLineListIndex = lookForFirstNewLine(endPos, firstModifLine, 0);

	//We modify lines after the \n (if exists), and decrement their start position
	//with deleted text size
	modifyLineListStartPos(newLineListIndex + 1, -(int)amount);

	myText.erase(startPosition, amount);

	//Reconstruct the text formatted vector

	if(text != "")
	{
		//Not perfect
		setCaretPosition(startPosition);
		insertText(text, startPosition);
	}
	else
	{
		reconstructSomeFormattedText(firstModifLine, newLineListIndex, -(int)amount, textArea);
		//std::string textToModify;
		////Construction of a temporary string for tests, to configure the new line list
		//if(myFormattedText.size() == 1)
		//{
		//	textToModify = myText;
		//}
		//else 
		//{
		//	if(newLineListIndex == myFormattedText.size() - 1)
		//	{
		//		//If we have to go till the end
		//		textToModify = myText.substr(myFormattedText[firstModifLine].startPosition, 
		//			myText.size());

		//	}
		//	else
		//	{
		//		textToModify = myText.substr(myFormattedText[firstModifLine].startPosition, 
		//			myFormattedText[newLineListIndex].startPosition -  myFormattedText[firstModifLine].startPosition 
		//			+ myFormattedText[newLineListIndex].length - amount - 1);
		//	}

		//	//Suppression des lignes devenues obsolètes, à partir de celle qui suit 
		//	//la première modifiée, jusqu'à la fin, ou la ligne précédent le premier \n
		//	for(unsigned int i = firstModifLine + 1; i <= newLineListIndex /*- 1*/; i++)
		//	{
		//		myFormattedText.erase(myFormattedText.begin() + (firstModifLine + 1));
		//	}
		//}

		//std::string textTest;
		//int numberInsertions = 0;
		//int debut = myFormattedText[firstModifLine].startPosition;
		//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();

		////Penser à virer le \n
		////Penser au cas où le texte à ajouter contient un \n. La recherche du prochain \n ne sera alors pas correcte
		//for(unsigned int i = 0; i < textToModify.size(); i++)
		//{
		//	textTest += textToModify[i];

		//	if(textToModify[i] == '\n' ||textToModify[i] == '\r\n')
		//	{
		//		FormattedText format;
		//		format.startPosition = debut + i + 1;//i + pos;

		//		myFormattedText.insert(myFormattedText.begin() + firstModifLine + numberInsertions + 1, format);
		//		numberInsertions++;
		//		textTest = "";
		//		//myNewLineList.push_back(debut + i);
		//		//retrier = true;

		//		//On revient un caractère en arrière, ie, celui qui a dépassé
		//		//i--;
		//	}
		//	else
		//	{
		//		//texteTest += textToModify[i];

		//		if(getFont()->getTextWidth(textTest, getFontSize()) > textArea.width)
		//		{

		//			FormattedText format;
		//			format.startPosition = debut + i;//i + pos;

		//			myFormattedText.insert(myFormattedText.begin() + firstModifLine + numberInsertions + 1, format);
		//			numberInsertions++;
		//			textTest = "";

		//			//On revient un caractère en arrière, ie, celui qui a dépassé
		//			i--;
		//		}
		//	}
		//}

		configureFormattedText();	
		setCaretPosition(startPosition);
		resetSelection();
		configureScrollBars();
		//adjustCaret();

		invalidate();
	}
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void TextField::adjustCaret()
//{
//	if(getCaretPosition() > getText().size())
//		setCaretPosition(getText().size());
//
//	if(getSelectionEnd() > getText().size())
//		setSelectionEnd(getText().size());
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool TextField::handleMouseWheel_impl(MouseEvent& ev)
{
	getScrollBarV()->handleMouseWheel(ev);

	invalidate();

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool TextField::handleTextEntered_impl(KeyboardEvent& ev)
{
	if(ev.getCharacter() == 13)
	{
		std::string s;
		s += '\n';
		insertText(s, getCaretPosition());
	}

	BaseTextWidget::handleTextEntered_impl(ev);

	////Si on supprime un caractère écrit
	//if (ev.getCharacter() == (int) '\b')
	//{			
	//	handleDeleting(getCaretPosition() - 1);
	//}
	////If we have some selected text, replace it
	//else if(getSelectionStart() != getSelectionEnd())
	//{
	//	std::string s;
	//	s += (char) ev.getCharacter();

	//	replaceTextRange(s, getSelectionStart(), getSelectionEnd());
	//}
	////Ajout de texte au texte en train d'être tapé
	////else if(ev.Text.Unicode != 13)
	//else if(ev.getCharacter() >= 32)
	//{
	//	std::string s;
	//	s += ev.getCharacter();
	//	insertText(s, getCaretPosition());
	//}

	ev.use(); 
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::onLostFocus()
{
	BaseWidget::onLostFocus();

	resetSelection();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::setText(const std::string& text)
{
	myText = "";
	myFormattedText.clear();
	appendText(text);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::configureScrollBars()
{
	//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	IntRect textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	getScrollBarV()->setPageSize((float)myFormattedText.size());
	getScrollBarV()->setVisibleAmount(static_cast<float>(textArea.height / getFontSize()));
	getScrollBarV()->setStepSize(1);
	//getScrollBarV()->correctPagePos();

	float value = getScrollBarV()->getValue();

	int nbElementsDisplayArea = static_cast<int>((getHeight()- textArea.y) / getFontSize());
	unsigned int caretLine = getCaretLine();

	TextField::LineList list = getFormattedText();
	unsigned int firstDisplayedLine = static_cast<unsigned int>(value * (myFormattedText.size() - nbElementsDisplayArea) + 0.5f);

	if(caretLine < firstDisplayedLine || caretLine > (firstDisplayedLine + nbElementsDisplayArea - 1))
	{
		getScrollBarV()->setValue(0.f);
		getScrollBarV()->modifyBlockPagePosition(caretLine - nbElementsDisplayArea + 1);
	}
}

unsigned int TextField::getCaretLine()
{
	return firstModifiedLine(getCaretPosition());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::setScrollBarV(PtrScrollBar scrollbar)
{
	PtrScrollBar zeScroll = getScrollBarV();
	IntRect dim = zeScroll->getWidgetDimensions();
	zeScroll = scrollbar;
	zeScroll->setDimensions(dim);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::update(unsigned int time)
{
	myTimeAccumulator += time;
	const unsigned int interval = 330;

	//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	IntRect textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();

	if(myIsDragging)
	{
		if(myTimeAccumulator > interval)
		{
			if(myMousePos.y < textArea.y)
			{
				getScrollBarV()->modifyBlockPagePosition(-1);
				myTimeAccumulator = 0;
			}
			else if(myMousePos.y > textArea.y + textArea.height)
			{
				getScrollBarV()->modifyBlockPagePosition(1);
				myTimeAccumulator = 0;
			}
		}
	}

	BaseTextWidget::update(time);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TextField::onDimensionsChanged()
{
	BaseTextWidget::onDimensionsChanged();

	myFormattedText.clear();
	FormattedText format;
	format.startPosition = 0;
		
	myFormattedText.push_back(format);

	//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	IntRect textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	reconstructSomeFormattedText(0, 0, 0, textArea);
	configureFormattedText();
	configureScrollBars();
}

} //end namespace
