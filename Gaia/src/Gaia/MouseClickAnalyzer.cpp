///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/MouseClickAnalyzer.h"

#include <ctime>

namespace gaia
{
const float MouseClickAnalyzer::TIME_OUT_DOUBLE_CLICK = 0.33f;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MouseClickAnalyzer::MouseClickAnalyzer(void)
:myNumberOfClicks(0)
,myLastButton(MouseButton::NO_BUTTON)
,myIsDoubleClick(false)
,myIsOkForClick(true)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MouseClickAnalyzer::~MouseClickAnalyzer(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool MouseClickAnalyzer::updateDoubleClick(const MouseEvent& ev, const Point& posSouris)
{
	if(isDoubleClick())
	{
		//For now, the GUI ignores mouse pressed events.
		//So, the only way to reset after a double click and to take into 
		//account theses events, is to face to a mouse released.
		if(ev.type == Event::MOUSE_RELEASED)
		{
			myIsDoubleClick = false;
			myIsOkForClick = true;
			return false;
		}
	}

	//if it is not a mouse pressed, no need to continue
	if(ev.type != Event::MOUSE_PRESSED)
	{
		return true;
	}

	myNumberOfClicks++;
	myIsDoubleClick = false;

	//If elapsed time is ok, the button corresponds, the mouse didn't move, 
	//and we pressed the mouse twice
	if(myTimer.elapsedTime() < TIME_OUT_DOUBLE_CLICK &&
		myLastButton == ev.getButton() &&
		myLastPosition == posSouris &&
		myNumberOfClicks >= 2)
	{
		myIsDoubleClick = true;
		myNumberOfClicks = 0;
		myIsOkForClick = false;
	}
	else if(myTimer.elapsedTime() > TIME_OUT_DOUBLE_CLICK)
	{
		myNumberOfClicks = 1;
		myTimer.reset();
		//myIsDoubleClick = false;
		//myIsOkForClick = true;
	}

	myLastPosition = posSouris;
	myLastButton = ev.getButton();
	//myIsDoubleClick = false;
	myIsOkForClick = true;
	return true;
}

void MouseClickAnalyzer::setDoubleClickHandled(bool handled)
{
	if (!handled) 
		myIsDoubleClick = false;
}

} //end namespace