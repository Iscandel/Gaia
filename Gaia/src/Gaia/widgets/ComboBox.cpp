///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ComboBox.h"
//#include "Gaia/widgets/BaseListBoxItem.h"
#include "Gaia/widgets/TextBox.h"
#include "Gaia/widgets/TextListBoxItem.h"
#include "Gaia/widgets/Button.h"
#include "Gaia/widgets/ScrollBar.h"

namespace gaia
{
//const std::string ComboListBox::myWidgetType = "ComboListBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ComboListBox::ComboListBox(const std::string& name , int x, int y, int width, int height)
:ListBox(name, x, y, width, height)
,myClickCounter(0)
{
	copyProperties<ComboListBox>();
	//To send listBox events to the scrollbar in catch input mode
	propagateEventsToChildren(true);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ComboListBox::ComboListBox(const std::string& name, const IntRect& dimensions)
:ListBox(name, dimensions)
,myClickCounter(0)
{
	copyProperties<ComboListBox>();
	propagateEventsToChildren(true);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ComboListBox::handleMousePressed_impl(MouseEvent& ev)
{
	//The listbox caught the mouse inputs, so we need to distribute manually
	//events to the scrollbar
	//PtrWidget widget;
	//widget = getScrollBarV()->getChildAt(ev.getX(), ev.getY());
	//if(widget)
	//{
	//	ev.myWidget = widget.get();
	//	widget->handleMousePressed(ev);
	//}
	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ComboListBox::handleMouseReleased_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		Point point = convertToMyCoordinates(Point(ev.getX(), ev.getY()));
		if(getScrollBarV()->testCollision(point.x, point.y))
			getScrollBarV()->handleMouseReleased(ev);
		else
		{
			myClickCounter++;

			if(myClickCounter == 2)
			{
				releaseMouseInputs();
				setVisible(false);
				myClickCounter = 0;
				Event ev(this);
				onSelectedIndexChanged(ev);
			}
		}
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ComboListBox::handleMouseHover_impl(MouseEvent& ev)
{
	int index = getIndexAt(Point(ev.getX(), ev.getY()));
	if(index >= 0)
	{
		myItems[index]->handleMouseHover(ev);
		resetIndices();
		addIndex(index);
		invalidate();
	}

	ev.use();
	return ev.isHandled();
}

///////////////////////////////////////////////////////////////////////////////
//=============================================================================
///////////////////////////////////////////////////////////////////////////////

//const std::string ComboBox::myWidgetType = "ComboBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ComboBox::ComboBox(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name, x, y, width, height)
,myNumberElementsDisplayed(10)
,PREFIX_TEXTBOX("_TextBoxComboBox")
,PREFIX_LISTBOX("_ListBoxComboBox")
,PREFIX_BUTTON("_ButtonComboBox")
//,SUFFIX("__")
{
	copyProperties<ComboBox>();
	getTextBox()->subscribeMousePressed(my_bind(&ComboBox::onClicCombo, this));
	getButton()->subscribeMousePressed(my_bind(&ComboBox::onClicCombo, this));
	getListBox()->setVisible(false);
	getListBox()->subscribeSelectedIndexChanged(my_bind(&ComboBox::onNewSelection, this));

	getTextBox()->setEnabled(false);

	setNumberElementsDisplayed(10);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ComboBox::ComboBox(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myNumberElementsDisplayed(10)
,PREFIX_TEXTBOX("_TextBoxComboBox")
,PREFIX_LISTBOX("_ListBoxComboBox")
,PREFIX_BUTTON("_ButtonComboBox")
//,SUFFIX("__")
{
	copyProperties<ComboBox>();
	getTextBox()->subscribeMousePressed(my_bind(&ComboBox::onClicCombo, this));
	getButton()->subscribeMousePressed(my_bind(&ComboBox::onClicCombo, this));
	getListBox()->setVisible(false);
	getListBox()->subscribeSelectedIndexChanged(my_bind(&ComboBox::onNewSelection, this));

	getTextBox()->setEnabled(false);

	setNumberElementsDisplayed(10);

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrTextBox ComboBox::getTextBox()
{
	const std::string name = PREFIX_TEXTBOX + getName();// + SUFFIX;
	if(!isChildPresent(name))
	{
		createChild("TextBox", name);
	}
	return getChild<gaia::TextBox>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrComboListBox ComboBox::getListBox()
{
	const std::string name = PREFIX_LISTBOX + getName();// + SUFFIX;
	if(!isChildPresent(name))
	{
		createChild("ComboListBox", name);
	}
	return getChild<gaia::ComboListBox>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrButton ComboBox::getButton()
{
	const std::string name = PREFIX_BUTTON + getName();// + SUFFIX;
	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}
	return getChild<gaia::Button>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBox::addItem(const std::string& item)
{
	getListBox()->addItem(PtrTextListBoxItem(new TextListBoxItem(item)));
	size_t numberItems = getListBox()->getItemList().size();
	PtrLayoutInfos infos = getListBox()->getLayoutInfos();
	infos->setHeightInfos(static_cast<int>(numberItems * getListBox()->getFontSize()));
	getListBox()->setLayoutInfos(infos);

	getListBox()->getScrollBarV()->setPageSize(static_cast<float>(myNumberElementsDisplayed));

	//getListBox()->setDimensions(
	//	getListBox()->getX(), 
	//	getListBox()->getY(), 
	//	getListBox()->getWidth(), 
	//	static_cast<int>(numberItems * getListBox()->getFontSize()));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBox::onClicCombo(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		moveToForeground();
		getListBox()->setVisible(true);//getListBox()->isVisible());
		getListBox()->catchMouseInputs();
	}
	//We use event to avoid it to be distributed to the TextBox and ListBox
	ev.use();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBox::onNewSelection(Event&)
{
	PtrTextListBoxItem item = std::dynamic_pointer_cast<TextListBoxItem>(getListBox()->getSelectedItem());
	if(item)
	{
		std::string val = item->getText();
		//std::string val = item->getValue();
		getTextBox()->setText(val);
	}
}

void ComboBox::setNumberElementsDisplayed(unsigned int number)
{
	myNumberElementsDisplayed = number;

	size_t numberItems = getListBox()->getItemList().size();
	PtrLayoutInfos infos = getListBox()->getLayoutInfos();
	if(infos)
	{
		infos->setHeightInfos(static_cast<int>(myNumberElementsDisplayed * getListBox()->getFontSize()));
		getListBox()->setLayoutInfos(infos);
	}
	else
	{
		
		getListBox()->setDimensions(
			getListBox()->getX(), 
			getListBox()->getY(), 
			getListBox()->getWidth(), 
			static_cast<int>(myNumberElementsDisplayed * getListBox()->getFontSize()));
	}

	
	getListBox()->getScrollBarV()->setStepSize(1.f);
	getListBox()->getScrollBarV()->setVisibleAmount(static_cast<float>(myNumberElementsDisplayed));
	getListBox()->getScrollBarV()->setPageSize(numberItems);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ComboBox::clearItemList()
{
	getListBox()->clearItemList();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
const std::string& ComboBox::getSelectedItem()
{
	return getTextBox()->getText();
}

};
