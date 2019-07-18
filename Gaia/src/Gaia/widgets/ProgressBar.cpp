///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ProgressBar.h"

namespace gaia
{
//const std::string ProgressBar::myWidgetType = "ProgressBar";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ProgressBar::ProgressBar(const std::string& name, 
						 int x, 
						 int y, 
						 int width, 
						 int height)
:BaseWidget(name, x, y, width, height)
,myPercentage(0.f)
,myDirection(HORIZONTAL)
,mySense(LTRBTT)
{
	copyProperties<ProgressBar>();
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ProgressBar::ProgressBar(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myPercentage(0.f)
,myDirection(HORIZONTAL)
,mySense(LTRBTT)
{
	copyProperties<ProgressBar>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBar::setValue(float perc)
{
	myPercentage = perc < 0.f ? 0.f : perc > 1.f ? 1.f : perc;

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBar::setValue(int perc)
{
	setValue(perc / 100.f);
	//myPercentage = perc < 0 ? 0.f : perc > 100 ? 1.f : perc / 100.f;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressBar::modifiyValue(float value)
{
	setValue(getValue() + value);
	//myPercentage += value;

	//if(myPercentage > 1.f) myPercentage = 1.f;
	//else if(myPercentage < 0.f) myPercentage = 0.f;
}

} //end namespace