///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/ScrollBar.h"
#include "Gaia/widgets/Button.h"
#include "Gaia/tools/Binder.h"
//#include "Gaia/widgetRenderers/ProprietesScrollBarBaseRenderer.h"
#include "Gaia/tools/Tools.h"
#include "Gaia/widgetRenderers/ScrollBarBaseRenderer.h"


namespace gaia
{
//const std::string ScrollBar::myWidgetType = "ScrollBar";
const unsigned int ScrollBar::SCROLLING_RATE = 330;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ScrollBar::ScrollBar(const std::string& name, int x, int y, int width, int height)
:BaseWidget(name, x, y, width, height)
,myOrientation(ScrollBar::VERTICAL)
,myPageSize(0)
,myValue(0.f)
,myPagePos(0.f)
,myVisibleAmount(0.f)
,myIncreaseButtonIsPressed(false)
,myDecreaseButtonIsPressed(false)
,myThumbIsPressed(false)
,PREFIX_INCREASE_BUTTON("_IncreaseButton")
,PREFIX_DECREASE_BUTTON("_DecreaseButton")
,PREFIX_THUMB("_Thumb")
{
	copyProperties<ScrollBar>();
	setFocusable(false);
	initButtons();

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
ScrollBar::ScrollBar(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myOrientation(ScrollBar::VERTICAL)
,myPageSize(0)
,myValue(0.f)
,myPagePos(0)
,myVisibleAmount(0.f)
,myIncreaseButtonIsPressed(false)
,myDecreaseButtonIsPressed(false)
,myThumbIsPressed(false)
,PREFIX_INCREASE_BUTTON("_IncreaseButton")
,PREFIX_DECREASE_BUTTON("_DecreaseButton")
,PREFIX_THUMB("_Thumb")
{
	copyProperties<ScrollBar>();
	setFocusable(false);
	initButtons();
}


void ScrollBar::initButtons()
{
	getDecreaseButton()->enableDoubleClick(false);
	getDecreaseButton()->subscribeMousePressed(my_bind(&ScrollBar::clickButtons, this));
	getDecreaseButton()->subscribeMouseReleased(my_bind(&ScrollBar::buttonReleased, this));
	getDecreaseButton()->subscribeWidgetExited(my_bind(&ScrollBar::ButtonsExited, this));

	getIncreaseButton()->enableDoubleClick(false);
	getIncreaseButton()->subscribeMousePressed(my_bind(&ScrollBar::clickButtons, this));
	getIncreaseButton()->subscribeMouseReleased(my_bind(&ScrollBar::buttonReleased, this));
	getIncreaseButton()->subscribeWidgetExited(my_bind(&ScrollBar::ButtonsExited, this));

	getThumb()->subscribeMousePressed(my_bind(&ScrollBar::clickButtons, this));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrButton ScrollBar::getDecreaseButton()
{
	const std::string name = PREFIX_DECREASE_BUTTON + getName();

	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}

	//return GuiManager::getInstance()->getWidget<gaia::Button>(PREFIX_INCREASE_BUTTON + getName() + SUFFIXE_BOUTON_HAUT );
	return getChild<gaia::Button>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrButton ScrollBar::getIncreaseButton()
{
	const std::string name = PREFIX_INCREASE_BUTTON + getName();
	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}

	//return GuiManager::getInstance()->getWidget<gaia::Button>(PREFIX_DECREASE_BUTTON + getName() + SUFFIXE_BOUTON_BAS );
	return getChild<gaia::Button>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrButton ScrollBar::getThumb()
{
	const std::string name = PREFIX_THUMB + getName();
	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}

	//return GuiManager::getInstance()->getWidget<gaia::Button>(PREFIX_THUMB + getName() + SUFFIXE_THUMB );
	return getChild<gaia::Button>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::onValueChanged(float valeur)
{
	if(E_onValueChanged != NULL)
		E_onValueChanged(valeur);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ScrollBar::handleMouseReleased_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT && myThumbIsPressed)
	{
		myThumbIsPressed = false;

		//Adjust page position to set an allowed page position value 
		//(mainly according to the stepsize)
		correctPagePos(); 

		//Re-compute corrected value using the new page position
		//and set visual position
		updatePosition(0);

		releaseMouseInputs();
	}

	ev.use(); 
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ScrollBar::handleMouseHover_impl(MouseEvent& ev)
{
	//if(getThumb()->getWidgetState() == BaseWidget::CLICKED)
	if(myThumbIsPressed)
	{
		if(myPageSize > myVisibleAmount)
		{
			Point coords(ev.getX(), ev.getY());
			if(myRenderer)
			{
				float pos = ((ScrollBarBaseRenderer*)myRenderer)->
					valueFromThumbPos(coords - myOffsetThumbClick);

				setValue(pos);
				onValueChanged(getValue());
			}
		}
	}
	ev.use(); 
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool ScrollBar::handleMouseWheel_impl(MouseEvent& ev)
{
	if(myPageSize > myVisibleAmount)
	{
		if(ev.getWheelDelta() > 0.f)
			updatePosition(-1);
		else
			updatePosition(1);
		onValueChanged(getValue());
	}
	ev.use(); 
	return true;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::setValue(float value) 
{
	myValue = value < 0.f ? 0.f : value > 1.f ? 1.f : value;
	correctPagePos();
	setThumbPosition();
	//Call onValueChanged ?
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::setVisibleAmount(float hauteur)
{
	myVisibleAmount = hauteur;
	correctPagePos();
	setThumbPosition();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::setStepSize(float stepSize)
{
	myStepSize = stepSize;
	correctPagePos();
	setThumbPosition();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::setPageSize(float size)
{
	if(size < 0.f)
	{
		throw IllegalArgument("Page size must be a positive value : "
					+ tools::numToString(size));
	}

	//Vérifier la taille de la zone de rendu

	myPageSize = size;
	//correctPagePos();

	//Check if the page position is still valid after having resized
	adjustPagePosition();

	//Update the new value according to the new page size
	computeValue();

	//Compute the visual thumb position according to the new value
	//setThumbPosition();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::updatePosition(int multiplier)
{
	//Update the page position
	myPagePos += myStepSize * multiplier;

	//Check and adjust validity
	adjustPagePosition();

	//Compute the new value
	computeValue();

	//Compute the visual position
	setThumbPosition();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::computeValue()
{
	//Handle special cases
	if(std::abs(myPageSize - myVisibleAmount) < 0.0001 ||
	   myPageSize < myVisibleAmount)
	{
		myValue = 0.f;
	}
	else
	{
		myValue = myPagePos / (myPageSize - myVisibleAmount);
		myValue = myValue < 0.f ? 
				  0.f : myValue > 1.f ? 1.f : myValue;
	}
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::setThumbPosition()
{
	if(myRenderer)
	{
		static_cast<ScrollBarBaseRenderer*>(myRenderer)->setThumbPosition();
	}
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::modifyBlockPagePosition(int multiplier)
{
	if(myPageSize > myVisibleAmount)
	{
		updatePosition(multiplier);
		onValueChanged(getValue());
	}

	//myTimeAccumulator = 0;
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::correctPagePos()
{
	myPagePos = myValue * (myPageSize - myVisibleAmount);

	int closest = tools::closestInt(myPagePos / myStepSize);
	myPagePos = closest * myStepSize;

	//Check the page position validity
	adjustPagePosition();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::adjustPagePosition()
{
	if(myPageSize < myVisibleAmount)
	{
		myPagePos = std::max(myPagePos, 0.f);
	}
	else
	{
		myPagePos = myPagePos > (myPageSize - myVisibleAmount) ? 
			(myPageSize - myVisibleAmount) : myPagePos < 0 ? 0 : myPagePos;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::update(unsigned int elapsedTime)
{
	myTimeAccumulator += elapsedTime;
	
	if(myTimeAccumulator > SCROLLING_RATE) //330 ms
	{
		//getDecreaseButton()->getWidgetState() == BaseWidget::CLICKED
		if(myDecreaseButtonIsPressed) 
		{
			modifyBlockPagePosition(-1);
		}
		else if(myIncreaseButtonIsPressed)
		{
			if(myPageSize > myVisibleAmount)
			{
				modifyBlockPagePosition(1);
			}
		}

		myTimeAccumulator = 0;
	}

	BaseWidget::update(elapsedTime);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::clickButtons(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
	{
		if(ev.getSource()->getName() == getDecreaseButton()->getName())
		{
			myDecreaseButtonIsPressed = true;
			modifyBlockPagePosition(-1);
		}
		else if(ev.getSource()->getName() == getIncreaseButton()->getName())
		{
			myIncreaseButtonIsPressed = true;
			modifyBlockPagePosition(1);
		}
		else if(ev.getSource()->getName() == getThumb()->getName())
		{
			myThumbIsPressed = true;
			catchMouseInputs();

			///Nb : We are in the thumb coordinate system
			if(myOrientation == ScrollBar::VERTICAL)
				myOffsetThumbClick.y = ev.getY();
			else
				myOffsetThumbClick.x = ev.getX();
		}

		myTimeAccumulator = 0;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ScrollBar::buttonReleased(MouseEvent&)
{
	myIncreaseButtonIsPressed = false;
	myDecreaseButtonIsPressed = false;
	myThumbIsPressed = false; //Not useful I think
	myTimeAccumulator = 0;
}

void ScrollBar::ButtonsExited(Event&)
{
	myIncreaseButtonIsPressed = false;
	myDecreaseButtonIsPressed = false;
	myTimeAccumulator = 0;
}

} //end namespace
