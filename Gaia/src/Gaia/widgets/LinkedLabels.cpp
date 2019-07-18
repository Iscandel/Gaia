#include "Gaia/widgets/LinkedLabels.h"
#include "Gaia/widgets/WidgetList.h"


namespace gaia
{

//const std::string LinkedLabels::myWidgetType = "LinkedLabels";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LinkedLabels::LinkedLabels(const std::string& name, 
						   int x, 
						   int y, 
						   int width, 
						   int height)
:Label(name, x, y, width, height)
//,myIsSelected(false)
{
	copyProperties<LinkedLabels>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LinkedLabels::LinkedLabels(const std::string& name, const IntRect& dimensions)
:Label(name, dimensions)
//,myIsSelected(false)
{
	copyProperties<LinkedLabels>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LinkedLabels::onSelected()
{
	setTextColor(mySelectionColor);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LinkedLabels::onUnselected()
{
	setTextColor(myNormalColor);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LinkedLabels::setColors(const Color& selectionne, const Color& normal)
{
	myNormalColor = normal;
	mySelectionColor = selectionne;
}

} //end namespace
