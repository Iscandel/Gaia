#include "Gaia/widgetRenderers/ListBoxSimpleRenderer.h"
#include "Gaia/widgets/BaseListBoxItem.h"
#include "Gaia/widgets/ScrollBar.h"

namespace gaia
{
ListBoxSimpleRenderer::ListBoxSimpleRenderer(PtrWidget w) 
:ListBoxBaseRenderer(w) 
,myBackgroundColor(250, 250, 250)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBoxSimpleRenderer::draw_impl(BaseGraphics* Gfx)
{
	if(myWidget->isOpaque())
	{
		drawBackground(Gfx);
	}

	drawItems(Gfx);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBoxSimpleRenderer::drawBackground(BaseGraphics* Gfx)
{
	Gfx->drawRectangle(
		Point(0,0),//myWidget->getX(), myWidget->getY()), 
		myWidget->getWidth(), 
		myWidget->getHeight(), 
		myBackgroundColor);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ListBoxSimpleRenderer::drawItems(BaseGraphics* Gfx)
{
	int firstItem = getFirstVisibleItem();
	const ListBox::ItemList& list = myWidget->getItemList();

	ListBox::ItemList::const_iterator it = list.begin() + firstItem;
	//const ListBox::SelectedIndicesList& indices = myWidget->getSelectedIndices();

	IntRect area = getItemArea();

	//int numIndex = 0;
	for(int num = 0; it != list.end(); num++, ++it)
	{
		//while(numIndice < indices.size() && indices[num]
		(*it)->drawItem(
			myWidget, 
			myWidget->isSelected(num + firstItem),
			Gfx, 
			area.x, 
			area.y + num * (*it)->getHeight());
	}
	//pour tous les items dans la zone d'affichage
	//item->dessiner(x, y);
	//Ne pas oublier de passer le Gfx à l'item
}

void ListBoxSimpleRenderer::setBackgroundColor(const Color& color)
{
	myBackgroundColor = color;
}

} //end namespace