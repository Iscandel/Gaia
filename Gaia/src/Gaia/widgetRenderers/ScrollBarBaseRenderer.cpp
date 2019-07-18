///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/ScrollBarBaseRenderer.h"
#include "Gaia/widgets/Button.h"

namespace gaia
{
void ScrollBarBaseRenderer::draw_impl(BaseGraphics*)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
float ScrollBarBaseRenderer::valueFromThumbPos(const Point& minEndThumb) //TO DO Vertical / Horiz !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	Rect<double> thumbArea = getThumbArea();
	int thumbHeight = myWidget->getThumb()->getHeight();

	//Thumb position relatively to the thumb extent
	double thumbY = minEndThumb.y - thumbArea.y;

	return (static_cast<float>(thumbY / (thumbArea.height - thumbHeight)));

	//setThumbPosition(minEndThumb); //Appelée par setValue()
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBarBaseRenderer::setThumbPosition()
{
	Rect<double> thumbArea = getThumbArea();
	gaia::PtrButton thumb = myWidget->getThumb();

	if(myWidget->getOrientation() == ScrollBar::VERTICAL)
	{
		thumb->setPosition(
			thumb->getX(),
			static_cast<int>(thumbArea.y + myWidget->getValue() * (thumbArea.height - thumb->getHeight())));
	}
	else
	{
		thumb->setPosition(
			static_cast<int>(thumbArea.x + myWidget->getValue() * (thumbArea.width - thumb->getWidth())),
			thumb->getY());
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Rect<double> ScrollBarBaseRenderer::getThumbArea()	//TO DO Vertical / Horiz !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	const std::string areaName = "thumb";

	int yDecrease = myWidget->getDecreaseButton()->getY();
	int DecreaseHeight = myWidget->getDecreaseButton()->getHeight();
	int IncreaseHeight = myWidget->getIncreaseButton()->getHeight();
	
	Rect<double> rect(
		0., 
		(double)yDecrease + DecreaseHeight, 
		(double)myWidget->getWidth(), 
		(double)myWidget->getHeight() - (yDecrease + DecreaseHeight) - IncreaseHeight);

	if(myAreas.find(areaName) != myAreas.end())
	{
		//rect = myAreas[areaName];

		rect.x = myAreas[areaName].x * myWidget->getWidth();
		rect.y = myAreas[areaName].y * myWidget->getHeight();

		//If relative coords
		//if(myAreas[areaName].width < 1.)
			rect.width = myAreas[areaName].width * myWidget->getWidth();

		//If relative coords
		//if(myAreas[areaName].height < 1.)
			rect.height = myAreas[areaName].height * myWidget->getHeight();
	}

	return rect;
}

} //end namespace