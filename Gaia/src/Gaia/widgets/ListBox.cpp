///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ListBox.h"
#include "Gaia/widgets/ScrollBar.h"
#include "Gaia/widgets/BaseListBoxItem.h"

#include "Gaia/widgetRenderers/ListBoxSimpleRenderer.h"

namespace gaia
{
//const std::string ListBox::myWidgetType = "ListBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ListBox::ListBox(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name,x, y, width, height)
,myIsDragging(false)
,myIsControlPressed(false)
,myIsShiftPressed(false)
,mySelectionType(SIMPLE_SELECTION)
,myRowHeight(0)
,PREFIX_SCROLLBARV("_VerticalScrollBar")
,PREFIX_SCROLLBARH("_HorizontalScrollBar")
//,SUFFIX("__")
{
	copyProperties<ListBox>();
	getScrollBarV();
	//setTextColor(Color(0,0,0));
	//setFontSize(30);

	//addItem("Bonjour");
	//addItem("ok");
	//addItem("oui");
	//addItem("Bien");
	//addItem("Lol");
	//addItem("Héhé");
	//addItem("Bonjour");
	//addItem("Alors");
	//addItem("C'est ça");
	//addItem("Que dis-tu");
	//addItem("Parfait");
	//addItem("Oki");
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ListBox::ListBox(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myIsDragging(false)
,myIsControlPressed(false)
,myIsShiftPressed(false)
,mySelectionType(SIMPLE_SELECTION)
,myRowHeight(0)
,PREFIX_SCROLLBARV("_VerticalScrollBar")
,PREFIX_SCROLLBARH("_HorizontalScrollBar")
//,SUFFIX("__")
{
	copyProperties<ListBox>();
	getScrollBarV();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::onSelectedIndexChanged(Event& ev)
{
	if(E_onSelectedIndexChanged != NULL) 
		E_onSelectedIndexChanged(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrScrollBar ListBox::getScrollBarV()
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
bool ListBox::handleMouseWheel_impl(MouseEvent& ev)
{
	getScrollBarV()->handleMouseWheel(ev);

	invalidate();

	ev.use();
	return ev.isHandled();
}

void ListBox::configureScrollBars()
{
	//Rect<double> textArea = dynamic_cast<TplTextWidgetRenderer<TextField>*>(myRenderer)->getTextArea();
	IntRect textArea = static_cast<ListBoxBaseRenderer*>(myRenderer)->getItemArea();
	getScrollBarV()->setPageSize(myItems.size());
	getScrollBarV()->setVisibleAmount(static_cast<float>(textArea.height / getFontSize()));
	getScrollBarV()->setStepSize(1);
	//getScrollBarV()->correctPagePos();

	//float value = getScrollBarV()->getValue();

	//int nbElementsDisplayArea = static_cast<int>((getHeight()- textArea.y) / getFontSize());
	//unsigned int caretLine = getCaretLine();

	//TextField::LineList list = getFormattedText();
	//unsigned int firstDisplayedLine = static_cast<unsigned int>(value * (myFormattedText.size() - nbElementsDisplayArea) + 0.5f);

	//if(caretLine < firstDisplayedLine || caretLine > (firstDisplayedLine + nbElementsDisplayArea - 1))
	//{
	//	getScrollBarV()->setValue(0.f);
	//	getScrollBarV()->modifyBlockPagePosition(caretLine - nbElementsDisplayArea + 1);
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::addItem(PtrBaseListBoxItem item)
{
	if(item->getWidth() == 0)
	{

		//Rect<double> area = static_cast<ListBoxBaseRenderer*>(myRenderer)->getItemArea(); //To modify ?
		IntRect area = static_cast<ListBoxBaseRenderer*>(myRenderer)->getItemArea(); //To modify ?
		//int itemHeight = getFixedRowHeight() == 0 ? item->getHeight() : getFixedRowHeight();
		//item->setDimensions(static_cast<int>(area.x), 
		//					static_cast<int>(area.y), 
		//					static_cast<int>(area.width), 
		//					itemHeight);
		item->setPosition(area.x, area.y);

		if(getFixedRowHeight() != 0)
		{
			item->setDimensions(item->getX(), item->getY(), area.width, getFixedRowHeight());
		}
		else
		{
			item->setDimensions(item->getX(), item->getY(), item->getWidth() == 0 ? area.width : item->getWidth(), item->getHeight());
		}

		//gerer le resize du widget qui modifie la taille des items...
	}

	myItems.push_back(item);

	configureScrollBars(); 
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::removeItem(PtrBaseListBoxItem item)
{
	for(unsigned int i = 0; i < myItems.size(); i++)
	{
		if(myItems[i] == item)
		{
			myItems.erase(myItems.begin() + i);
			if(removeIndex(i))
			{
				Event ev(this);
				onSelectedIndexChanged(ev);
			}
			return;
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::removeItem(unsigned int index)
{
	if(index < myItems.size())
	{
		myItems.erase(myItems.begin() + index);
		if(removeIndex(index))
		{
			Event ev(this);
			onSelectedIndexChanged(ev);
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::selectItem(unsigned int index)
{
	if(index >= myItems.size())
		throw IllegalArgument("Invalid ListBox index");

	resetIndices();
	addIndex(index);

	Event ev(this);
	onSelectedIndexChanged(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::addSelectionInterval(unsigned int indexMin, unsigned int indexMax)
{
	for(unsigned int i = indexMin; i <= indexMax; i++)
	{
		addIndex(i);
	}

	Event ev(this);
	onSelectedIndexChanged(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::selectItems(const std::vector<unsigned int>& indices)
{
	std::vector<unsigned int>::const_iterator itMax = std::max_element(indices.begin(), indices.end());
	if(*itMax >= myItems.size())
		throw IllegalArgument("Invalid ListBox index");

	//Reset selection
	resetIndices();

	for(unsigned int i = 0; i < indices.size(); i++)
	{
		addIndex(indices[i]);
	}

	Event ev(this);
	onSelectedIndexChanged(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrBaseListBoxItem ListBox::getSelectedItem() const
{
	if(mySelectedIndices.size() > 0)
	{
		assert(myItems.size() != 0);

		ItemList::const_iterator it = myItems.begin() + *(mySelectedIndices.begin());
		return *it;
	}

	return PtrBaseListBoxItem();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ListBox::ItemList ListBox::getSelectedItems() const
{
	std::vector<PtrBaseListBoxItem> res;

	SelectedIndicesList::const_iterator it = mySelectedIndices.begin();
	for(; it != mySelectedIndices.end(); ++it)
	{
		res.push_back(myItems[*it]);
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int ListBox::getSelectedIndex() const
{
	int res = -1;
	if(mySelectedIndices.size())
	{
		res = *(mySelectedIndices.begin());
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
const ListBox::SelectedIndicesList& ListBox::getSelectedIndices() const
{
	return mySelectedIndices;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrBaseListBoxItem ListBox::getItemAt(const Point& pos) const
{
	int index = getIndexAt(pos);
	if(index >= 0 && index < static_cast<int>(myItems.size()))
	{
		ItemList::const_iterator it = myItems.begin() + index;
		return *it;
	}

	return PtrBaseListBoxItem();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int ListBox::getIndexAt(const Point& pos) const
{
	int index;
	index = static_cast<ListBoxSimpleRenderer*>(myRenderer)->computeSelectedItem(pos);

	return index;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::updateItems()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::handleMousePressed_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		myIsDragging = true;

		int index = getIndexAt(Point(ev.getX(), ev.getY()));
		if(index >= 0)
		{
			//Forward event to the targeted item
			myItems[index]->handleMousePressed(ev);
			if(myIsControlPressed && getSelectionType() == MULTILINES)
			{
				bool isSel = isSelected(index);

				//We cannot remove the last index
				if(mySelectedIndices.size() != 1 ||
					!isSel)
					//!myItems[index]->isSelected())
				{
					SelectedIndicesList vec = getSelectedIndices();

					if(isSel)
					{
						SelectedIndicesList::iterator it = 
							std::find(vec.begin(), vec.end(), index);
						vec.erase(it);
						//removeIndex(index);
					}
					else
					{
						vec.push_back(index);
						//addIndex(index);
					}
					selectItems(vec);
				}
			}
			else
			{
				selectItem(index);
				//resetIndices();
				////myItems[index]->setSelectionner(true);
				//addIndex(index);
			}
		}
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::handleMouseReleased_impl(MouseEvent& ev)
{
	myIsDragging = false;

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::handleMouseHover_impl(MouseEvent& ev)
{
	if(myIsDragging)
	{
		int index = getIndexAt(Point(ev.getX(), ev.getY()));
		if(index >= 0 && !myIsControlPressed)
		{
			selectItem(index);
		}
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::handleKeyPressed_impl(KeyboardEvent& ev)
{
	if(ev.getKey() == Keyboard::LCONTROL ||
		ev.getKey() == Keyboard::RCONTROL)
	{
		myIsControlPressed = true;
	}

	ev.use();

	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::handleKeyReleased_impl(KeyboardEvent& ev)
{
	if(ev.getKey() == Keyboard::LCONTROL ||
		ev.getKey() == Keyboard::RCONTROL)
	{
		myIsControlPressed = false;
	}

	ev.use();

	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
const ListBox::ItemList& ListBox::getItemList() const
{
	return myItems;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::addIndex(unsigned int index)
{
	mySelectedIndices.push_back(index);

	std::sort(mySelectedIndices.begin(), mySelectedIndices.end());

	mySelectedIndices.erase(
        std::unique(mySelectedIndices.begin(), mySelectedIndices.end()),
        mySelectedIndices.end() );
	
	
	//mySelectedIndices.unique();
	//mySelectedIndices.sort();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::isSelected(unsigned int index)
{
	return std::find(mySelectedIndices.begin(), mySelectedIndices.end(), index)
			!= mySelectedIndices.end();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ListBox::removeIndex(unsigned int index)
{
	SelectedIndicesList::iterator it = 
		std::find(mySelectedIndices.begin(), mySelectedIndices.end(), index);
	
	if(it != mySelectedIndices.end())
	{
		mySelectedIndices.erase(it);
		return true;
	}
	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::resetIndices()
{
	mySelectedIndices.clear();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string ListBox::getSelectedValue() const
{
	PtrBaseListBoxItem item = getSelectedItem();
	if(item)
	{
		return item->getValue();
	}

	return "";
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> ListBox::getSelectedValues() const
{
	std::vector<std::string> res;

	std::vector<PtrBaseListBoxItem> items = getSelectedItems();
	for(unsigned int i = 0; i < items.size(); i++)
	{
		res.push_back(items[i]->getValue());
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int ListBox::getItemListSize() const
{
	return myItems.size();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBox::clearItemList()
{
	for(unsigned int i = 0; i < myItems.size(); i++)
	{
		myItems.erase(myItems.begin() + i);
		if(removeIndex(i))
		{
			Event ev(this);
			onSelectedIndexChanged(ev);
		}
	}
}


	
void ListBox::clearSelection()
{
	for(unsigned int i = 0; i < myItems.size(); i++)
	{
		if(removeIndex(i))
		{
			Event ev(this);
			onSelectedIndexChanged(ev);
		}
	}
}

} //end namespace