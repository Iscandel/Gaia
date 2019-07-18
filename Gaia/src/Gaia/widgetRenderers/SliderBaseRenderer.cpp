///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgetRenderers/SliderBaseRenderer.h"
#include "Gaia/widgets/Button.h"

namespace gaia
{
void SliderBaseRenderer::draw_impl(BaseGraphics* Gfx)
{
	if(imageExists(myWidget->getStrWidgetState()))
	{
		Gfx->drawImage(myImages[myWidget->getStrWidgetState()], 
					   0,
					   0,
					   myWidget->getWidth(), 
					   myWidget->getHeight()
		);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int SliderBaseRenderer::valueFromThumbPos(const Point& minEndThumb)
{
	Rect<double> thumbArea = getThumbArea();
	int min = myWidget->getMinimum();
	int max = myWidget->getMaximum();
	
	if(myWidget->getOrientation() == Slider::VERTICAL)
	{
		int thumbHeight = myWidget->getThumb()->getHeight();

		//Thumb position relatively to the thumb extent
		double thumbY = minEndThumb.y - thumbArea.y;

		return (static_cast<int>((thumbY / (thumbArea.height - thumbHeight)) * (max - min)));
	}
	else
	{
		int thumbWidth = myWidget->getThumb()->getWidth();

		//Thumb position relatively to the thumb extent
		double thumbX = minEndThumb.x - thumbArea.x;

		return (static_cast<int>((thumbX / (thumbArea.width - thumbWidth)) * (max - min)));
	}

	//setThumbPosition(minEndThumb); //Appelée par setValue()
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SliderBaseRenderer::setThumbPosition()
{
	Rect<double> thumbArea = getThumbArea();
	gaia::PtrButton thumb = myWidget->getThumb();
	int min = myWidget->getMinimum();
	int max = myWidget->getMaximum();
	float perc =  (myWidget->getValue() - min) / (float)(max - min);

	if(myWidget->getOrientation() == Slider::VERTICAL)
	{
		thumb->setPosition(
			thumb->getX(),
			static_cast<int>(thumbArea.y + perc * (thumbArea.height - thumb->getHeight())));
	}
	else
	{
		thumb->setPosition(
			static_cast<int>(thumbArea.x + perc * (thumbArea.width - thumb->getWidth())),
			thumb->getY());
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Rect<double> SliderBaseRenderer::getThumbArea()
{
	const std::string areaName = "thumb";

	//int yDecrease = myWidget->getDecreaseButton()->getY();
	//int DecreaseHeight = myWidget->getDecreaseButton()->getHeight();
	//int IncreaseHeight = myWidget->getIncreaseButton()->getHeight();
	
	//Rect<double> rect(
	//	0., 
	//	(double)yDecrease + DecreaseHeight, 
	//	(double)myWidget->getWidth(), 
	//	(double)myWidget->getHeight() - (yDecrease + DecreaseHeight) - IncreaseHeight);

		Rect<double> rect(
		0., 
		0.,
	    myWidget->getWidth(),
		myWidget->getHeight());

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