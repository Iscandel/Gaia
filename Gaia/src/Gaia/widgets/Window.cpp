///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/Window.h"
#include "Gaia/widgets/Button.h"
#include "Gaia/widgetRenderers/WindowImageRenderer.h"

namespace gaia
{
TitleBar::TitleBar(const std::string& name, 
	   int x, 
	   int y, 
	   int width, 
	   int height)
:BaseWidget(name, x, y, width, height)
,myIsResizing(false)
,PREFIX_CLOSEBUTTON("_CloseButton")
{
	getCloseButton();
	copyProperties<TitleBar>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
TitleBar::TitleBar(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,PREFIX_CLOSEBUTTON("_CloseButton")
{
	getCloseButton();
	copyProperties<TitleBar>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool TitleBar::handleMousePressed_impl(MouseEvent& ev)
{
	myIsResizing = true;
	catchMouseInputs();

	myMousePos = Point(ev.getX(), ev.getY());

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool TitleBar::handleMouseReleased_impl(MouseEvent& ev)
{
	myIsResizing = false;
	releaseMouseInputs();

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool TitleBar::handleMouseHover_impl(MouseEvent& ev)
{
	if(myIsResizing && getParent())
	{
		Point delta = Point(ev.getX(), ev.getY()) - myMousePos;
		IntRect dim = getParent()->getWidgetDimensions();
		getParent()->setDimensions(dim.x + delta.x, dim.y + delta.y, dim.width, dim.height);
	}

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrButton TitleBar::getCloseButton()
{
	const std::string name = PREFIX_CLOSEBUTTON + getName();

	if(!isChildPresent(name))
	{
		createChild("Button", name);
	}

	return getChild<gaia::Button>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Window::Window(const std::string& name, 
	   int x, 
	   int y, 
	   int width, 
	   int height)
:BaseWidget(name, x, y, width, height)
,myIsResizing(false)
,myIsLeftResizing(false)
,myIsTopResizing(false)
,myIsTopLeftResizing(false)
,myIsRightResizing(false)
,myIsTopRightResizing(false)
,myIsBottomResizing(false)
,myIsBottomLeftResizing(false)
,myIsBottomRightResizing(false)
,myBehaviour(DESTROY)
,PREFIX_TITLEBAR("_TitleBar")
{
	myIsForegroundWidget = true;

	getTitleBar()->getCloseButton()->subscribeMouseReleased(my_bind(&Window::clickCloseButton, this));
	copyProperties<Window>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Window::Window(const std::string& name, const IntRect& dimensions)
:BaseWidget(name, dimensions)
,myIsResizing(false)
,myIsLeftResizing(false)
,myIsTopResizing(false)
,myIsTopLeftResizing(false)
,myIsRightResizing(false)
,myIsTopRightResizing(false)
,myIsBottomResizing(false)
,myIsBottomLeftResizing(false)
,myIsBottomRightResizing(false)
,myBehaviour(DESTROY)
,PREFIX_TITLEBAR("_TitleBar")
{
	myIsForegroundWidget = true;

	getTitleBar()->getCloseButton()->subscribeMouseReleased(my_bind(&Window::clickCloseButton, this));
	copyProperties<Window>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrTitleBar Window::getTitleBar()
{
	const std::string name = PREFIX_TITLEBAR + getName();

	if(!isChildPresent(name))
	{
		createChild("TitleBar", name);
	}

	return getChild<gaia::TitleBar>(name);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Window::handleMousePressed_impl(MouseEvent& ev)
{
	myIsResizing = true;
	myResizingPosition = dynamic_cast<WindowImageRenderer*>(myRenderer)->getEdge(ev.getX(), ev.getY());
	
	if(myResizingPosition != PrivResizing::NONE)
		catchMouseInputs();

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Window::handleMouseReleased_impl(MouseEvent& ev)
{
	myIsResizing = false;
	myResizingPosition = PrivResizing::NONE;
	releaseMouseInputs();

	ev.use();
	return ev.isHandled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Window::handleMouseHover_impl(MouseEvent& ev)
{
	//if(myIsResizing)
	//{
	//	IntRect dim = getWidgetDimensions();
	//	setDimensions(dim.x, dim.y, ev.getX(), dim.height);
	//}

	IntRect dim = getWidgetDimensions();
	if(myResizingPosition == PrivResizing::LEFT)
		setDimensions(dim.x + ev.getX(), dim.y, dim.width - ev.getX(), dim.height);
	else if(myResizingPosition == PrivResizing::TOP_LEFT)
		setDimensions(dim.x + ev.getX(), dim.y + ev.getY(), dim.width - ev.getX(), dim.height - ev.getY());
	else if(myResizingPosition == PrivResizing::BOTTOM_LEFT)
		setDimensions(dim.x + ev.getX(), dim.y, dim.width, ev.getY());
	else if(myResizingPosition == PrivResizing::BOTTOM)
		setDimensions(dim.x, dim.y, dim.width, ev.getY());
	else if(myResizingPosition == PrivResizing::BOTTOM_RIGHT)
		setDimensions(dim.x, dim.y, ev.getX(), ev.getY());
	else if(myResizingPosition == PrivResizing::RIGHT)
		setDimensions(dim.x, dim.y, ev.getX(), dim.height);
	else if(myResizingPosition == PrivResizing::TOP_RIGHT)
		setDimensions(dim.x, dim.y + ev.getY(), ev.getX(), dim.height);

	ev.use();
	return ev.isHandled();
}

void Window::clickCloseButton(MouseEvent&)
{
	if(myBehaviour == DESTROY) 
	{
		setVisible(false);
		destroy();
	}
	else 
	{
		setVisible(false);
	}
}

void Window::onGainedFocus()
{
	BaseWidget::onGainedFocus();
	moveToForeground();
}

} //end namespace
