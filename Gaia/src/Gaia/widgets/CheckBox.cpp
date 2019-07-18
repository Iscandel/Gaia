#include "Gaia/widgets/CheckBox.h"

namespace gaia
{
//const std::string CheckBox::myWidgetType = "CheckBox";

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
CheckBox::CheckBox(const std::string& name, 
				   int x, 
				   int y, 
				   int width, 
				   int height)
:BaseWidget(name, x, y, width, height)
,myIsChecked(false)
,myIsTextOnRight(true)
,myIsStateChanging(false)
{
	copyProperties<CheckBox>();
	enableDoubleClick(false);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
CheckBox::CheckBox(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myIsChecked(false)
,myIsTextOnRight(true)
,myIsStateChanging(false)
{
	copyProperties<CheckBox>();
	enableDoubleClick(false);
}

void CheckBox::onStateChanged()
{
	if(E_onStateChanged)// && isStateChanging)
	{
		Event ev(this);
		E_onStateChanged(ev);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool CheckBox::handleMouseReleased_impl(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
		setChecked(!isChecked());

	ev.use();

	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBox::setChecked(bool checked) 
{
	myIsChecked = checked;

	//Prevent recursive and infinite calls : myOnStateChanged() { setChecked(!getChecked()); ...}
	if(!myIsStateChanging)
	{
		myIsStateChanging = true;
		onStateChanged();
		myIsStateChanging = false;
	}
	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBox::adjustSize()
{
	int newWidth = 
		static_cast<int>(getFont()->getTextWidth(getText(), getFontSize()) 
						 + getHeight() + 1);

	setDimensions(getX(), getY(), newWidth, getHeight());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBox::setText(const std::string& text)
{
	myText = text;
	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBox::onWidgetEntered()
{
	BaseWidget::onWidgetEntered();

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CheckBox::onWidgetExited()
{
	BaseWidget::onWidgetExited();

	invalidate();
}

} //end namespace