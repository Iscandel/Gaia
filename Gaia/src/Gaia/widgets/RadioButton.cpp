#include "Gaia/widgets/RadioButton.h"


namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
RadioButton::RadioButton(const std::string& name, 
						   int x, 
						   int y, 
						   int width, 
						   int height)
:BaseWidget(name, x, y, width, height)
,myIsStateChanging(false)
{
	copyProperties<RadioButton>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
RadioButton::RadioButton(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myIsStateChanging(false)
{
	copyProperties<RadioButton>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void RadioButton::onStateChanged()
{
	if(E_onStateChanged)// && isStateChanging)
	{
		Event ev(this);
		E_onStateChanged(ev);
	}
}

bool RadioButton::handleMouseReleased_impl(MouseEvent& ev)
{
	if(!isSelected())
	{
		setSelected(true);
		invalidate();
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void RadioButton::onSelected()
{
	//Avoid infinite recursive calls, ex -> myOnStateChanged() { w->setSelected(!w->isSelected());}
	if(!myIsStateChanging)
	{
		myIsStateChanging = true;
		onStateChanged();
		myIsStateChanging = false;
	}
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void RadioButton::onUnselected()
{
	//Avoid infinite recursive calls -> myOnStateChanged() { w->setSelected(!w->isSelected());}
	if(!myIsStateChanging)
	{
		myIsStateChanging = true;
		onStateChanged();
		myIsStateChanging = false;
	}
}

} //end namespace
