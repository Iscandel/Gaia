///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseTextWidget.h"
#include "Gaia/widgetRenderers/TextWidgetBaseRenderer.h"

namespace gaia
{
//const std::string BaseTextWidget::myWidgetType = "BaseTextWidget";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseTextWidget::BaseTextWidget(const std::string& name,
								 int x,
								 int y,
								 int width,
								 int height)
:BaseWidget(name, x, y, width, height)
,myIsReadOnly(false)
,myIsDragging(false)
{
	copyProperties<BaseTextWidget>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseTextWidget::BaseTextWidget(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myIsReadOnly(false)
,myIsDragging(false)
{
	copyProperties<BaseTextWidget>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseTextWidget::onTextChanged()
{
	if(E_onTextChanged != NULL)	
	{
		Event ev(this);
		E_onTextChanged(ev);
	}

	notifyObservers();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseTextWidget::adjustCaret()
{
	if(getCaretPosition() > getText().size())
		setCaretPosition((unsigned int)getText().size());

	if(getSelectionEnd() > getText().size())
		setSelectionEnd((unsigned int)getText().size());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseTextWidget::handleMousePressed_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		myIsDragging = true;
		catchMouseInputs();

		if(myRenderer)
		{
			int posWidgetX = dynamic_cast<TextWidgetBase*>(myRenderer)->computeCaretPosition(
													Point(ev.getX(), ev.getY()));

			if(posWidgetX >= 0)
			{
				myCaret = posWidgetX;
				myFirstSelection = myCaret;
				myLastSelection = myFirstSelection;
			}

			invalidate();
		}
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseTextWidget::handleMouseHover_impl(MouseEvent& ev)
{
	myMousePos.x = ev.getX(); myMousePos.y = ev.getY();

	if(myIsDragging)
	{
		if(myRenderer)
		{
			int posWidgetX = dynamic_cast<TextWidgetBase*>(myRenderer)->computeCaretPosition(
												Point(ev.getX(), ev.getY()));
			if(posWidgetX >= 0)
			{
				moveSelection(posWidgetX - myLastSelection);
			}
		}
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseTextWidget::handleMouseReleased_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		myIsDragging = false;
		releaseMouseInputs();

		int posWidgetX = dynamic_cast<TextWidgetBase*>(myRenderer)->
					computeCaretPosition(Point(ev.getX(), ev.getY()));

		if(posWidgetX >= 0)
		{
			myLastSelection = posWidgetX;
			myCaret = posWidgetX;
		}
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseTextWidget::handleKeyPressed_impl(KeyboardEvent& ev)
{
	if(ev.getKey() == Keyboard::LEFT)
	{
		//Selection
		if(ev.isShiftPressed)
		{
			moveSelection(-1);
		}
		else
		{
			setCaretPosition(getCaretPosition() - 1);
			resetSelection();
		}
		notifyObservers();
	}

	else if(ev.getKey() == Keyboard::RIGHT)
	{
		//Selection
		if(ev.isShiftPressed)
		{
			moveSelection(1);
		}
		else
		{
			setCaretPosition(getCaretPosition() + 1);
			resetSelection();
		}
		notifyObservers();
	}

	else if(ev.getKey() == Keyboard::UP)
	{
		int nouvellePos = 
			dynamic_cast<TextWidgetBase*>(myRenderer)->computeCaretPosition(false);

		if(nouvellePos != getCaretPosition())
		{
			setCaretPosition(nouvellePos);
		}
		notifyObservers();
	}
	else if(ev.getKey() == Keyboard::DOWN)
	{
		int nouvellePos = 
			dynamic_cast<TextWidgetBase*>(myRenderer)->computeCaretPosition(true);

		if(nouvellePos != getCaretPosition())
		{
			setCaretPosition(nouvellePos);
		}
		notifyObservers();
	}
	else if(ev.getKey() == Keyboard::DEL)
	{
		handleDeleting(getCaretPosition());
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseTextWidget::handleTextEntered_impl(KeyboardEvent& ev)
{
	//If we delete a character
	if (ev.getCharacter() == '\b')
	{
		handleDeleting(getCaretPosition() - 1);
	}
	//If we have some selected text, replace it
	else if(getSelectionStart() != getSelectionEnd())
	{
		std::string s;
		s += (char) ev.getCharacter();

		replaceTextRange(s, getSelectionStart(), getSelectionEnd());
	}
	//Insert character
	else if(ev.getCharacter() >= 32)
	{
		std::string s;
		s += (char) ev.getCharacter();
		insertText(s, getCaretPosition());
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseTextWidget::handleDeleting(unsigned int posIfNotSelected)
{
	if (myText.size() > 0)
	{
		if(myCaret >= 0)
		{
			unsigned int selectionStart = getSelectionStart();
			unsigned int selectionEnd = getSelectionEnd();

			if(selectionStart != selectionEnd)
			{
				deleteTextRange(selectionStart, selectionEnd);
			}
			else
			{
				if(posIfNotSelected < myText.size())
					deleteText(posIfNotSelected, 1);
			}
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseTextWidget::setCaretPosition(unsigned int pos)
{
	ICaret::setCaretPosition(pos, myText.size());

	invalidate();
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseTextWidget::moveSelection(unsigned int amount)
{
	ICaret::moveSelection(amount, myText.size());

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string BaseTextWidget::getSelectedText()
{
	return myText.substr(getSelectionStart(), getSelectionEnd() - getSelectionStart());
}

} //end namespace
