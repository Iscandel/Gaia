///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/widgets/BaseWidget.h"

#include "Gaia/widgetRenderers/WidgetRenderer.h"

#include "Gaia/WidgetFactoryManager.h"
#include "Gaia/GuiManager.h"
#include "Gaia/FocusWidgetManager.h"

#include <cmath>

namespace gaia
{
//const std::string BaseWidget::myWidgetType = "BaseWidget";

PropertySystem BaseWidget::mySharedPropertySystem;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseWidget::BaseWidget(const std::string& name, int x, int y, int width, int height)
:myIsVisible(true)
,myIsModal(false)
,myIsEnabled(true)
,myHasFocus(false)
,myIsFocusable(true)
,myNeedRedraw(true)
,myIsForegroundWidget(false)
,myName(name)
,myDummyWidgetType("a")
,myParent(NULL)
,myWidgetState(BaseWidget::NORMAL)
,myIsOpaque(true)
,myHandleDoubleClick(true)
,myToDestroy(false)
,myTimeAccumulator(0)
,myGraphics(NULL)
,myFocusWidgetManager(NULL)
,myRenderer(NULL)
,myPropagateEventsToChildren(false)
{
	myDimensions = IntRect(x, y, width, height);

	//We copy the shared properties to the current instance
	copyProperties<BaseWidget>();

	std::cout << "Constructed " << name << std::endl;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseWidget::BaseWidget(const std::string& name, const IntRect& dimensions)
:myIsVisible(true)
,myIsModal(false)
,myIsEnabled(true)
,myHasFocus(false)
,myIsFocusable(true)
,myNeedRedraw(true)
,myIsForegroundWidget(false)
,myName(name)
,myDummyWidgetType("a")
,myDimensions(dimensions)
,myToDestroy(false)
,myParent(NULL)
,myWidgetState(BaseWidget::NORMAL)
,myIsOpaque(true)
,myHandleDoubleClick(true)
,myTimeAccumulator(0)
,myGraphics(NULL)
,myFocusWidgetManager(NULL)
,myRenderer(NULL)
,myPropagateEventsToChildren(false)
{
	//We copy the shared properties to the current instance
	copyProperties<BaseWidget>();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseWidget::~BaseWidget(void)
{
	//WARNING. Never call shared_from_this() here !

	std::cout << "Destructed " << getName() << std::endl;
	////put in onDestruction ?
	//if(myFocusWidgetManager)
	//{
	//	releaseMouseInputs();
	//	setModal(false);
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onDestruction()
{	
	Event ev(this);
	//Traditionally corresponds to fireEvent()
	if(E_onDestruction != NULL)
		E_onDestruction(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onMousePressed(MouseEvent& ev)
{	
	//Traditionally corresponds to fireEvent()
	if(E_onMousePressed)// != NULL)
		E_onMousePressed(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onMouseReleased(MouseEvent& ev)
{
	if(E_onMouseReleased)// != NULL) 
		E_onMouseReleased(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onDoubleClick(MouseEvent& ev)
{
	if(E_onDoubleClick)// != NULL) 
		E_onDoubleClick(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onMouseHover(MouseEvent& ev)
{
	if(E_onMouseHover)// != NULL)
		E_onMouseHover(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onMouseWheel(MouseEvent& ev)
{
	if(E_onMouseWheel)// != NULL)
		E_onMouseWheel(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onKeyPressed(KeyboardEvent& ev)
{
	if(E_onKeyPressed)// != NULL) 
		E_onKeyPressed(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onKeyReleased(KeyboardEvent& ev)
{
	if(E_onKeyReleased)// != NULL) 
		E_onKeyReleased(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onTextEntered(KeyboardEvent& ev)
{
	if(E_onTextEntered)// != NULL) 
		E_onTextEntered(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onVisibility(VisibilityEvent& ev)
{
	if(E_onVisibiliy)// != NULL)
		E_onVisibiliy(ev);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onWidgetEntered()
{
	if(E_onEnter)// != NULL)
	{
		Event ev(this);
		E_onEnter(ev);
	}

	setWidgetState(BaseWidget::HOVER);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onWidgetExited()
{
	if(E_onExit)// != NULL)
	{
		Event ev(this);
		E_onExit(ev);
	}

	setWidgetState(BaseWidget::NORMAL);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onDimensionsChanged()
{
	if(E_onDimensionsChanged)// != NULL)
	{
		Event ev(this);
		E_onDimensionsChanged(ev);
	}

	//Resize children if they have relative dimensions
	for(unsigned int i = 0; i < myChildren.size(); i++)
	{
		myChildren[i]->resizeFromLayout();
		myChildren[i]->adjustClippingArea(); //Useless I think, done before
	
		//if(myChildren[i]->myLayoutInfos)
		//{
		//	IntRect dim = myChildren[i]->myLayoutInfos->getComputedDimensions(myChildren[i].get());
		//	myChildren[i]->setDimensions(dim);
		//}
	}

	if(myRenderer)
		myRenderer->resizeAreas();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setLayoutInfos(PtrLayoutInfos infos)
{
	myLayoutInfos = infos;
	resizeFromLayout();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::resizeFromLayout()
{
	if(myLayoutInfos)
	{
		IntRect dim = myLayoutInfos->getComputedDimensions(this);
		setDimensions(dim);
	}
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void BaseWidget::resizeChildIfRelativeDim(PtrWidget toResize)
//{
//	if(toResize->hasRelativeDimensions())
//	{
//		const Rect<double>& rect = toResize->getRelativeDimensions();
//		int xChild = static_cast<int>(rect.x * getWidth());
//		int yChild = static_cast<int>(rect.y * getHeight());
//		int childWidth = static_cast<int>(rect.width * getWidth());
//		int childHeight = static_cast<int>(rect.height * getHeight());
//		toResize->setDimensions(xChild, yChild, childWidth, childHeight);
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onGainedFocus()
{
	if(E_onGainedFocus != NULL)
	{
		Event ev(this);
		E_onGainedFocus(ev);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::onLostFocus()
{
	if(E_onLostFocus != NULL)
	{
		Event ev(this);
		E_onLostFocus(ev);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget BaseWidget::createChild(const std::string& type, const std::string& name)
{
	PtrWidget widget = GuiManager::getInstance()->createWidget(type, name);
	
	if(widget)
		add(widget);

	return widget;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget BaseWidget::reloadChild(const std::string& type, const std::string& name)
{
	PtrWidget widget = GuiManager::getInstance()->reloadWidget(type, name);

	return widget;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::add(PtrWidget w)
{
	//Check for circular inclusion parent <-> child
	if(!isDescendantFrom(w) && !isChildPresent(w->getName()))
	{
		if(getGraphics())
			w->setGraphics(getGraphics());
		//if(!myFocusWidgetManager)
		//	throw GuiException("No FocusWidgetManager set. Cannot add child.");
		w->affectFocusWidgetManager(myFocusWidgetManager);
		w->setParent(this);
		myChildren.push_back(w);

		//Move it to the right place, depending on it is a window or not
		w->moveToForeground();

		//Resize child if necessary
		w->resizeFromLayout();

		//Adjust the child's absolute clipping area
		w->adjustClippingArea();
		//resizeChildIfRelativeDim(w);
		invalidate();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::remove(PtrWidget w)
{
	for(size_t i = 0; i < myChildren.size(); i++)
	{
		if(myChildren[i] == w)
		{
			myChildren.erase(myChildren.begin() + i);
			w->adjustClippingArea();
			invalidate();
			return true;
		}
	}
	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::remove(unsigned int i)
{
	if(i < myChildren.size())
	{
		PtrWidget child = myChildren[i];
		myChildren.erase(myChildren.begin() + i);
		child->adjustClippingArea();
		invalidate();
		return true;
	}
	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::isEnabled() const
{
	if(myParent == NULL)
		return myIsEnabled;

	return myIsEnabled && myParent->isEnabled();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::hasFocus() const
{
	if(myParent == NULL)
		return myHasFocus;

	return myHasFocus && myParent->hasFocus();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget BaseWidget::getFocusedChild()
{
	//If we don't have the focus...
	if(!hasFocus())
		return PtrWidget();

	//Iterate children
	std::vector<PtrWidget>::reverse_iterator it = myChildren.rbegin();
	for(it; it != myChildren.rend(); ++it)
	{
		PtrWidget w = (*it)->getFocusedChild();
		if(w)
		{
			return w;
		}
	}

	return shared_from_this();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::isVisible() const 
{
	if(myParent == NULL) 
		return myIsVisible; 

	//if a parent is present, see first if it is visible
	return myIsVisible && myParent->isVisible();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setVisible(bool b)
{
	if(myIsVisible == b)
		return;

	VisibilityEvent ev(this, b);

	if(!b)
	{
		//~onInvisible
		onVisibility(ev);
	}
	else
	{
		//if it is going to be hidden, we release the focus
		requestFocus(false);

		//~onVisible
		onVisibility(ev);
	}

	myIsVisible = b;

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::requestFocus(bool b)
{
	//if(myHasFocus == b)
	//	return;

	if(!isEnabled() || !isVisible() || !isFocusable())
		return;

	if(b)
	{
		//GuiManager::getInstance()->releaseMouseInputs(); //Check this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		BaseWidget* p = getParent();
		if(p)
		{
			p->requestFocus(true);
		}

		if(!hasFocus())
			onGainedFocus();

		std::vector<PtrWidget>::reverse_iterator it = myChildren.rbegin();
		for(it; it != myChildren.rend(); ++it)
		{
			//if((*it)->hasFocus()) //check this
			{
				(*it)->requestFocus(false);
			}
		}
	}
	else
	{
		if(hasFocus())
			onLostFocus();
	}

	myHasFocus = b;

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setDimensions(const IntRect& dim)
{
	////If nothing changes, we stop here (NB: The renderer clipping area should always be tested for update)
	//if(myDimensions == dim)
	//	return;

	myDimensions = dim;

	//set negative values to 0
	myDimensions.width =std::max(0, myDimensions.width);
	myDimensions.height =std::max(0, myDimensions.height);

	////Adjust the clipping area
	//if(myRenderer)
	//{
	//	//const IntRect& rect = myRenderer->getClippingArea();

	//	//We check if we need to resize the clipping area
	//	if(!myRenderer->isFixedClippingArea())
	//	{
	//		myRenderer->setClippingArea(getScreenCoordinates());
	//	}
	//}
	adjustClippingArea();

	onDimensionsChanged();

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::adjustClippingArea()
{
	//Adjust the clipping area
	if(myRenderer)
	{
		//const IntRect& rect = myRenderer->getClippingArea();

		//We check if we need to resize the clipping area
		if(!myRenderer->isFixedClippingArea())
		{
			myRenderer->setClippingArea(getScreenCoordinates());
			invalidate();
		}
	}

	for(unsigned int i = 0; i < myChildren.size(); i++)
	{
		myChildren[i]->adjustClippingArea();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setDimensions(int x, int y, int width, int height)
{
	IntRect rect(x, y, width, height);
	setDimensions(rect);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void BaseWidget::setRelativeDimensions(const Rect<double>& dim) 
//{
//	myRelativeDimensions = dim;
//
//	//Resize, if relative dimensions are not 0, and if we have a parent
//	if(getParent() && hasRelativeDimensions())
//	{
//		setDimensions(static_cast<int>(getParent()->getWidth() * dim.x),
//					  static_cast<int>(getParent()->getHeight() * dim.y),
//					  static_cast<int>(getParent()->getWidth() * dim.width),
//					  static_cast<int>(getParent()->getHeight() * dim.height));
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//bool BaseWidget::hasRelativeDimensions() const
//{
//	const double EPS = 0.0001;
//
//	return(std::abs(myRelativeDimensions.x) > EPS ||
//		   std::abs(myRelativeDimensions.y) > EPS ||
//		   std::abs(myRelativeDimensions.width) > EPS ||
//		   std::abs(myRelativeDimensions.height) > EPS);
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string BaseWidget::getStrWidgetState()
{
	if(myWidgetState == BaseWidget::NORMAL)
		return "normal";
	if(myWidgetState == BaseWidget::HOVER)
		return "hover";
	if(myWidgetState == BaseWidget::CLICKED)
		return "click";
	
	throw GuiException("WidgetState not recognized and cannot be converted in string.");
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::testCollision(int x, int y)
{
	const IntRect& rect = getWidgetDimensions();

	return(x > rect.x  && 
		   x < rect.x + rect.width && 
		   y > rect.y   && 
		   y < rect.y + rect.height);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget BaseWidget::getChildAt(int x, int y)
{
	x -= getX();
	y -= getY();

	std::vector<PtrWidget>::reverse_iterator it = myChildren.rbegin();
	for(it; it != myChildren.rend(); ++it)
	{
		PtrWidget w = (*it)->getChildAt(x, y);
		if(w)
			return w;
	}

	if(isVisible() && testCollision(x + getX(), y + getY()))
		return shared_from_this();
	return PtrWidget();

	//std::vector<PtrWidget>::reverse_iterator it = myChildren.rbegin();
	//for(it; it != myChildren.rend(); ++it)
	//{
	//	if((*it)->isVisible() && 
	//	   (*it)->testCollision(x, y))
	//	{
	//		PtrWidget w = (*it)->getChildAt(x, y);
	//		return w ? w : (*it);
	//	}
	//}

	//return PtrWidget();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<PtrWidget> BaseWidget::getChildrenAt(int x, int y)
{
	//x -= getX();
	//y -= getY();

	//std::vector<PtrWidget> res;

	//std::vector<PtrWidget>::reverse_iterator it = myChildren.rbegin();
	//for(it; it != myChildren.rend(); ++it)
	//{
	//	if((*it)->isVisible() && 
	//	   (*it)->testCollision(x, y))
	//	{
	//		res.push_back(*it);
	//		std::vector<PtrWidget> enfants = (*it)->getChildrenAt(x, y);
	//		res.insert(res.end(), enfants.begin(), enfants.end());
	//	}
	//}

	//return res;

	x -= getX();
	y -= getY();

	std::vector<PtrWidget> res;

	std::vector<PtrWidget>::reverse_iterator it = myChildren.rbegin();
	for(it; it != myChildren.rend(); ++it)
	{
		if((*it)->isVisible() && 
		   (*it)->testCollision(x, y))
		{
			res.push_back(*it);
		}
		
		std::vector<PtrWidget> enfants = (*it)->getChildrenAt(x, y);
		res.insert(res.end(), enfants.begin(), enfants.end());
	}

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::isDescendantFrom(PtrWidget widget)
{
	//if we don't have any parent, we can't be a descendant from widget
	if(!getParent())
		return false;

	//We check if our parent name is the same as the widget name.
	if(getParent()->getName() == widget->getName())
		return true;

	//Otherwise, we continue recursively with our parent
	return getParent()->isDescendantFrom(widget);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::catchMouseInputs()
{
	if(!myFocusWidgetManager)
	{
		throw GuiException("No focus widget manager set. Did you forget to "
			"affect a parent widget ?" );
	}

	//if(hasFocus())
	if(isVisible() && isEnabled())
	{
		//myFocusWidgetManager->setWidgetCatchInputs(shared_from_this());
		myFocusWidgetManager->addWidgetCatchInputs(shared_from_this());
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::releaseMouseInputs()
{
	if(!myFocusWidgetManager)
	{
		throw GuiException("No focus widget manager set. Did you forget to "
			"affect a parent widget ?" );
	}

	//if(myFocusWidgetManager->getWidgetCaughtInput().get() == this)
	//{
	//	myFocusWidgetManager->setWidgetCatchInputs(PtrWidget());
	//}

	myFocusWidgetManager->releaseWidgetCaughtInput(shared_from_this());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setModal(bool b)
{
	if(!myFocusWidgetManager)
	{
		throw GuiException("No focus widget manager set. Did you forget to "
			"affect a parent widget ?" );
	}

	if(b)
	{
		myFocusWidgetManager->addModalWidget(shared_from_this());
	}
	else
	{
		myFocusWidgetManager->releaseModalWidget(shared_from_this());
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::draw(int xPosParent, int yPosParent) 
{
	if(myRenderer)
		myRenderer->draw(xPosParent, yPosParent);

	drawChildren(xPosParent, yPosParent);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::drawChildren(int xPosParent, int yPosParent)
{
	for(unsigned int i = 0; i< myChildren.size(); i++)
	{
		if(myChildren[i]->isVisible())
		{
			myChildren[i]->draw(xPosParent + getX(), yPosParent + getY());
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setWidgetRenderer(IWidgetRenderer* mr)
{
	//Remove and delete previous renderer
	if(myRenderer)
	{
		myRenderer->onReleasedFromWidget(shared_from_this());
		delete myRenderer;
	}

	myRenderer = mr;
	myRenderer->setWidget(shared_from_this());

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setGraphics(BaseGraphics* Gfx)
{
	//correct ?
	//if(myGraphics == Gfx)
	//	return;

	myGraphics = Gfx;
	
	for(unsigned int i = 0; i< myChildren.size(); i++)
	{
		myChildren[i]->setGraphics(Gfx);
	}

	invalidate();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::affectFocusWidgetManager(FocusWidgetManager* manager)
{
	myFocusWidgetManager = manager;
	for(unsigned int i = 0; i < myChildren.size(); i++)
	{
		myChildren[i]->affectFocusWidgetManager(manager);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::update(unsigned int elapsedTime)
{
	if(myRenderer)
		myRenderer->update(elapsedTime);

	std::vector<PtrWidget>::iterator it = myChildren.begin();
	for(it; it != myChildren.end();)
	{
		if((*it)->mustBeDestroyed())
		{
			it = myChildren.erase(it);
		}
		else
		{
			(*it)->update(elapsedTime);
			++it;
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleMousePressed(MouseEvent& ev)
{
	if(ev.getButton() == MouseButton::LEFT)
		setWidgetState(BaseWidget::CLICKED);

	requestFocus(true);

	//User function, if present
	onMousePressed(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		//Stuff for derived classes
		handled = handleMousePressed_impl(ev);
	}

	//If it is still not handled, distribute the event to parent
	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//MouseEvent ev(*this, Se.getX(), Se.getY(), Se.getButton());
			ev.myWidget = p;
			ev.myX += getX();
			ev.myY += getY();
			handled = p->handleMousePressed(ev);
		}
	}

	//ev.use();

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleMouseReleased(MouseEvent& ev)
{
	setWidgetState(BaseWidget::HOVER);

	onMouseReleased(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleMouseReleased_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//MouseEvent ev(*this, Se.getX(), Se.getY(), Se.getButton());
			ev.myWidget = p;
			ev.myX += getX();
			ev.myY += getY();
			handled = p->handleMouseReleased(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleDoubleClick(MouseEvent& ev)
{
	onDoubleClick(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleDoubleClick_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//MouseEvent ev(*this, Se.getX(), Se.getY(), Se.getButton());
			ev.myWidget = p;
			ev.myX += getX();
			ev.myY += getY();
			handled = p->handleDoubleClick(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleMouseHover(MouseEvent& ev)
{
	onMouseHover(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleMouseHover_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//MouseEvent ev(*this, Se.getX(), Se.getY(), Se.getWheelDelta(), Se.getButton());
			ev.myWidget = p;
			ev.myX += getX();
			ev.myY += getY();
			handled = p->handleMouseHover(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleMouseWheel(MouseEvent& ev)
{
	onMouseWheel(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleMouseWheel_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//MouseEvent ev(*this, Se.getX(), Se.getY(), Se.getButton());
			ev.myWidget = p;
			handled = p->handleMousePressed(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleKeyPressed(KeyboardEvent& ev)
{
	onKeyPressed(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleKeyPressed_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//KeyboardEvent ev(*this, Se.getX(), Se.getY(), Se.getButton());
			ev.myWidget = p;
			handled = p->handleKeyPressed(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleKeyReleased(KeyboardEvent& ev)
{
	onKeyReleased(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleKeyReleased_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			//KeyboardEvent ev(*this, ev.getKey());
			ev.myWidget = p;
			handled = p->handleKeyReleased(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool BaseWidget::handleTextEntered(KeyboardEvent& ev)
{
	onTextEntered(ev);

	bool handled = ev.isHandled();

	if(!handled)
	{
		handled = handleTextEntered_impl(ev);
	}

	if(!handled)
	{
		BaseWidget* p = getParent();
		if(p)
		{
			ev.myWidget = p;
			handled = p->handleTextEntered(ev);
		}
	}

	return handled;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setWidgetState(WidgetState e)
{
	myWidgetState = e;
}	

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::destroy()
{
	myToDestroy = true;
	if(getParent())
	{
		getParent()->remove(shared_from_this());
		myParent = NULL;
	}

	for(unsigned int i = 0; i < myChildren.size(); i++)
	{
		myChildren[i]->destroy();
	}

	if(myFocusWidgetManager)
	{
		releaseMouseInputs();
		setModal(false);
	}

	onDestruction();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::moveToForeground()
{
	if(getParent())
	{
		//PtrWidget last = getParent()->myChildren.back();
		int lastIndex = getParent()->myChildren.size() - 1;

		if(!myIsForegroundWidget)
		{
			for(unsigned int i = getParent()->myChildren.size() - 1; i >= 0; i--)
			{
				if(!getParent()->myChildren[i]->myIsForegroundWidget)
				{
					lastIndex = i;
					break;
				}
			}
		}

		for(unsigned int i = 0; i < getParent()->myChildren.size(); i++)
		{
			if(this == getParent()->myChildren[i].get())
			{
				while((int)i < lastIndex)
				{
					std::swap(getParent()->myChildren[i], getParent()->myChildren[i + 1]);//getParent()->myChildren.back());
					
					getParent()->myChildren[i]->invalidate();
					i++;
				}
				break;
			}
		}

		invalidate();
	}
}
	
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::moveToBackground() ////////////////////////////////////////////////////////////////////// to correct !!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	if(getParent())
	{
		for(unsigned int i = 0; i < getParent()->myChildren.size(); i++)
		{
			if(this == getParent()->myChildren[i].get())
			{
				std::swap(getParent()->myChildren[i], getParent()->myChildren.front());
			}
		}

		invalidate();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setPosition(int x, int y)
{
	int width = getWidth();
	int height = getHeight();

	setDimensions(IntRect(x, y, width, height));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Point BaseWidget::convertToMyCoordinates(const Point& posSouris)
{
	Point res = posSouris;
	res.x -= getX();
	res.y -= getY();
	/*while(Parent != NULL)
	{
		res.x -= Parent->getX();
		res.y -= Parent->getY();
		//Affecter le nouveau parent
	}*/
	if(myParent == NULL)
		return res;
	else
		return (myParent->convertToMyCoordinates(res));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
IntRect BaseWidget::getScreenCoordinates()
{
	if(myParent == NULL)
		return myDimensions;
	else
	{
		IntRect res = myDimensions;
		IntRect dim = myParent->getScreenCoordinates();
		res.x += dim.x;
		res.y += dim.y;
		
		return res;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//// Ajoute un nouveau widget enfant
/////////////////////////////////////////////////////////////////////////////////
//void BaseWidget::ajouterPropriete(PtrPropriete p)
//{
//	if(!myPropertySystem.existe(myWidgetType, p->getName()))
//	{
//		myPropertySystem.ajouterPropriete(myWidgetType, p);
//	}
//	else
//	{
//		//throw GuiException("Propriété " + p->getName() + " existe déjà et ne peut pas être ajoutée à ");// + getName());
//	}
//}

//bool BaseWidget::remplacerPropriete(PtrPropriete p)
//{
//	bool res = myPropertySystem.deleteProperty(myWidgetType, p->getName());
//	myPropertySystem.ajouterPropriete(myWidgetType, p);
//
//	return res;
//}

//=============================================================================
bool BaseWidget::isChildPresent(const std::string& name)
{
	for(unsigned int i = 0; i < myChildren.size(); i++)
	{
		if(myChildren[i]->getName() == name)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::addProperty(properties::PtrProperty p)
{
	if(myPropertySystem.exists(myDummyWidgetType, p->getName()))
	{
		throw GuiException("Property " + p->getName() + 
			" already exists and cannot be added to " + getName());
	}
	myPropertySystem.addProperty(myDummyWidgetType, p);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseWidget::setProperty(const std::string& name, const std::string& value)
{
	myPropertySystem.setProperty(myDummyWidgetType, *this, name, value);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string BaseWidget::getProperty(const std::string& name)
{
	return myPropertySystem.getProperty(myDummyWidgetType, name);
}

//=============================================================================
bool BaseWidget::deleteProperty(const std::string& name)
{
	return myPropertySystem.deleteProperty(myDummyWidgetType, name);
}

} //end namespace