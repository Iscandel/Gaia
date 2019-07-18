#include "Gaia/widgets/Slider.h"
#include "Gaia/widgets/Button.h"
#include "Gaia/tools/Binder.h"
#include "Gaia/tools/Tools.h"
#include "Gaia/widgetRenderers/SliderBaseRenderer.h"

namespace gaia
{
const unsigned int Slider::SCROLLING_RATE = 30;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Slider::Slider(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name, x, y, width, height)
,myOrientation(Slider::HORIZONTAL)
,myValue(0)
,myMinValue(0)
,myMaxValue(100)
,myThumbIsPressed(false)
,PREFIX_THUMB("_Thumb")
{
	copyProperties<Slider>();
	setFocusable(false);
	initThumb();

	//PtrLayoutInfos infos(new LayoutInfos);
	//infos->myPosition.myPositionType = LayoutInfos::UNIFORM;
	//infos->myPosition.myRawPos = "width - 4 - 17; 3";
	//infos->myWidthType.myPositionType = LayoutInfos::FIXED;
	//infos->myWidthType.myRawPos = "17";
	//infos->myHeightType.myPositionType = LayoutInfos::UNIFORM;
	//infos->myHeightType.myRawPos = "height - 4";

	//setLayoutInfos(infos);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Slider::Slider(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myOrientation(Slider::HORIZONTAL)
,myValue(0)
,myMinValue(0)
,myMaxValue(100)
,myThumbIsPressed(false)
,PREFIX_THUMB("_Thumb")
{
	copyProperties<Slider>();
	setFocusable(false);
	initThumb();
}

void Slider::initThumb()
{
	getThumb()->subscribeMousePressed(my_bind(&Slider::clickThumb, this));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrButton Slider::getThumb()
{
	const std::string name = PREFIX_THUMB + getName();
	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}

	//return GuiManager::getInstance()->getWidget<gaia::Button>(PREFIX_THUMB + getName() + SUFFIX_THUMB );
	return getChild<gaia::Button>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Slider::onValueChanged(float valeur)
{
	if(E_onValueChanged != NULL)
		E_onValueChanged(valeur);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Slider::handleMouseReleased_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT && myThumbIsPressed)
	{
		myThumbIsPressed = false;

		//Adjust page position to set an allowed page position value 
		//(mainly according to the stepsize)
		//correctPagePos(); 

		//Re-compute corrected value using the new page position
		//and set visual position
		//updatePosition(0);

		releaseMouseInputs();
	}

	ev.use(); 
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Slider::handleMouseHover_impl(MouseEvent& ev)
{
	if(myThumbIsPressed)
	{
		Point coords(ev.getX(), ev.getY());
		if(myRenderer)
		{
			int pos = ((SliderBaseRenderer*)myRenderer)->
				valueFromThumbPos(coords - myOffsetThumbClick);

			setValue(pos);
			onValueChanged(getValue());
		}
	}
	ev.use(); 
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Slider::setValue(int value) 
{
	int oldValue = myValue;
	myValue = value < myMinValue ? myMinValue : value > myMaxValue ? myMaxValue : value;

	//correctPagePos();
	setThumbPosition();

	if (oldValue != myValue)
		onValueChanged(myValue);
	//Call onValueChanged ?
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void ScrollBar::computeValue()
//{
//	//Handle special cases
//	if(std::abs(myPageSize - myVisibleAmount) < 0.0001 ||
//	   myPageSize < myVisibleAmount)
//	{
//		myValue = 0.f;
//	}
//	else
//	{
//		myValue = myPagePos / (myPageSize - myVisibleAmount);
//		myValue = myValue < 0.f ? 
//				  0.f : myValue > 1.f ? 1.f : myValue;
//	}
//}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Slider::setThumbPosition()
{
	if(myRenderer)
	{
		static_cast<SliderBaseRenderer*>(myRenderer)->setThumbPosition();
	}
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void ScrollBar::correctPagePos()
//{
//	myPagePos = myValue * (myPageSize - myVisibleAmount);
//
//	int closest = tools::closestInt(myPagePos / myStepSize);
//	myPagePos = closest * myStepSize;
//
//	//Check the page position validity
//	adjustPagePosition();
//}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void ScrollBar::adjustPagePosition()
//{
//	if(myPageSize < myVisibleAmount)
//	{
//		myPagePos = std::max(myPagePos, 0.f);
//	}
//	else
//	{
//		myPagePos = myPagePos > (myPageSize - myVisibleAmount) ? 
//			(myPageSize - myVisibleAmount) : myPagePos < 0 ? 0 : myPagePos;
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Slider::update(unsigned int elapsedTime)
{
	myTimeAccumulator += elapsedTime;
	
	if(myTimeAccumulator > SCROLLING_RATE) 
	{
		//getDecreaseButton()->getWidgetState() == BaseWidget::CLICKED
		if(myThumbIsPressed) 
		{
			//modifyBlockPagePosition(-1);
		}
		
		myTimeAccumulator = 0;
	}

	BaseWidget::update(elapsedTime);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Slider::clickThumb(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		myThumbIsPressed = true;
		catchMouseInputs();

		///Nb : We are in the thumb coordinate system
		if(myOrientation == Slider::VERTICAL)
			myOffsetThumbClick.y = ev.getY();
		else
			myOffsetThumbClick.x = ev.getX();

		myTimeAccumulator = 0;
	}
}

} //end namespace