///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/ListBoxBaseRenderer.h"
#include "Gaia/widgets/BaseListBoxItem.h"
#include "Gaia/widgets/ScrollBar.h"

namespace gaia
{
ListBoxBaseRenderer::ListBoxBaseRenderer(PtrWidget w)
:TplWidgetRenderer<ListBox>(w) 
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int ListBoxBaseRenderer::computeSelectedItem(const Point& pos)
{
	//Rect<double> area = getItemArea();
	IntRect area = getItemArea();
	int firstItem = getFirstVisibleItem();
	const ListBox::ItemList& list = myWidget->getItemList();

	for(unsigned int num = 0, i = firstItem; i < list.size(); num++, i++)
	{
		if(pos.x >= area.x && 
		   pos.x <= area.width && 
		   pos.y >= area.y + num * list[i]->getHeight() && 
		   pos.y <= area.y + (num + 1) * list[i]->getHeight())
		{
			return i;
		}
	}

	return -1;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int ListBoxBaseRenderer::getFirstVisibleItem()
{

	//Rect<double> area = getItemArea();
	IntRect area = getItemArea();
	const ListBox::ItemList& list = myWidget->getItemList();
	float value = myWidget->getScrollBarV()->getValue();

	int res = 0;
	//const float EPS = 1e-10;

	if(list.size() > 0)
	{
		if(list[0]->getHeight() == 0)
			return 0;
		int nbElementsDisplayArea = static_cast<int>((area.height) / (list[0]->getHeight()));

		res = static_cast<int>(value * (list.size() - nbElementsDisplayArea) + 0.5f);
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//Rect<double> ListBoxBaseRenderer::getItemArea()
IntRect ListBoxBaseRenderer::getItemArea()
{
	std::string areaName = "item";

	//Rect<double> rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
	IntRect rect(0, 0, myWidget->getWidth(), myWidget->getHeight());
	if(myAreas.find(areaName) != myAreas.end())
	{
		rect = myAreas[areaName];

		////if relative coords
		//rect.x = myAreas[areaName].x * myWidget->getWidth();

		////if relative coords
		//rect.y = myAreas[areaName].y * myWidget->getHeight();

		////if relative coords
		//rect.width = myAreas[areaName].width * myWidget->getWidth();

		//rect.height = myAreas[areaName].height * myWidget->getHeight();
	}

	return rect;
}
	
void ListBoxBaseRenderer::constructCacheHeight()
{
	ListBox::ItemList items = myWidget->getItemList();

	myHeights.resize(items.size());
	myHeights[0] = 0;

	for(unsigned int i = 1; i < items.size(); i++)
	{
		myHeights[i] = myHeights[i - 1] + items[i - 1]->getHeight();
	}
}

} //end namespace