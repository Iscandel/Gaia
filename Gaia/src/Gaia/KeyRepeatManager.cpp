#include "Gaia/KeyRepeatManager.h"
#include "Gaia/GuiManager.h"

namespace gaia
{
KeyRepeatManager::KeyRepeatManager(void)
:myInitialKeyRepeatTime(0)
,myKeyRepeatTime(0)
,myIsTextEnteredOk(false)
,myIsKeyPressedOk(false)
,myLastKeyPressedEvent(NULL, Event::END, Keyboard::COUNT, 0, false, false, false) 
,myLastTextEnteredEvent(NULL, Event::END, Keyboard::COUNT, 0, false, false, false) 
,TIME_OUT_REPEAT_FIRST(500)
,TIME_OUT_REPEAT(50)
{
}

void KeyRepeatManager::newKeyboardEvent(gaia::KeyboardEvent& ev)
{
	if(ev.type == gaia::Event::TEXT_ENTERED)
	{
		myLastTextEnteredEvent = ev;
		myIsTextEnteredOk = true;
	}
	else if(ev.type == gaia::Event::KEY_PRESSED)
	{
		if(!myIsKeyPressedOk)
		{
			myInitialKeyRepeatTime = 0;
			myLastKeyPressedEvent = ev;
			myIsKeyPressedOk = true;
		}
	}
	else if(ev.type == gaia::Event::KEY_RELEASED)
	{
		myIsTextEnteredOk = false;
		myIsKeyPressedOk = false;
	}
}

void KeyRepeatManager::manageKeyRepeat(unsigned int elapsedTime)
{
	//if(!isKeyRepeatEnabled())// || !myIsKeyPressed)
	//	return;

	if(myInitialKeyRepeatTime < TIME_OUT_REPEAT_FIRST)
	{
		myInitialKeyRepeatTime += elapsedTime;
		if(myInitialKeyRepeatTime >= TIME_OUT_REPEAT_FIRST)
		{
			//add the difference
			myKeyRepeatTime += elapsedTime - (myInitialKeyRepeatTime - TIME_OUT_REPEAT_FIRST);
			myInitialKeyRepeatTime = TIME_OUT_REPEAT_FIRST;
		}
	}
	else
	{
		myKeyRepeatTime += elapsedTime;
	}

	if(myInitialKeyRepeatTime >= TIME_OUT_REPEAT_FIRST && 
	   myKeyRepeatTime >= TIME_OUT_REPEAT)
	{
		if(myIsTextEnteredOk)
		{
			KeyboardEvent ev = myLastTextEnteredEvent;
			GuiManager::getInstance()->handleKeyboardEvent(ev);
			//gaia::GuiManager::getInstance()->processEvent(ev);
		}
		if(myIsKeyPressedOk)
		{
			KeyboardEvent ev = myLastKeyPressedEvent;
			GuiManager::getInstance()->handleKeyboardEvent(ev);
			//GuiManager::getInstance()->processEvent(ev);
		}
		myKeyRepeatTime = 0;
	}
}

} //end namespace