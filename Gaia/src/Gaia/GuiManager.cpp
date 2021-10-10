///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/GuiManager.h"
#include "Gaia/WidgetFactoryManager.h"
#include "Gaia/addFactory.h"
#include "Gaia/MouseClickAnalyzer.h"

#include "Gaia/addWidgetRendererFactory.h"

#include "Gaia/WidgetRendererManager.h"
#include "Gaia/WidgetLookManager.h"
#include "Gaia/WidgetLook.h"
#include "Gaia/addProperty.h"
#include "Gaia/FocusWidgetManager.h"

#include "Gaia/tools/Tools.h"

#include <iterator>

namespace gaia
{
GuiManager::GuiManager(void)
:myWidth(0)
,myHeight(0)
,myGraphics(NULL)
,myIsKeyRepeatEnabled(false)
,myInitialKeyRepeatTime(0)
,myKeyRepeatTime(0)
,myIsKeyPressed(false)
,myLastKeyPressedEvent(NULL, Event::END, Keyboard::COUNT, 0, false, false, false)  
,TIME_OUT_REPEAT_FIRST(500)
,TIME_OUT_REPEAT(50)
{
	//On ajoute les factory des widgets standard
	addDefinedFactories();

	addDefinedWidgetRendererFactories();

	addDefinedProperties();

	myFocusWidgetManager = new FocusWidgetManager;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
GuiManager::GuiManager(const Point& posSouris, BaseGraphics* gfx)
:myMousePosition(posSouris)
,myWidth(0)
,myHeight(0)
,myGraphics(gfx)
,myIsKeyRepeatEnabled(false)
,myInitialKeyRepeatTime(0)
,myKeyRepeatTime(0)
,myIsKeyPressed(false)
,myLastKeyPressedEvent(NULL,Event::END, Keyboard::COUNT, 0, false, false, false)  
,TIME_OUT_REPEAT_FIRST(500)
,TIME_OUT_REPEAT(50)
{
	addDefinedFactories();

	addDefinedWidgetRendererFactories();

	addDefinedProperties();

	myFocusWidgetManager = new FocusWidgetManager;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
GuiManager::~GuiManager(void)
{
	delete myGraphics;
	delete myFocusWidgetManager;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget GuiManager::createWidget(const std::string& type, const std::string& name)
{
	//PtrWidgetsFactory Factory = WidgetsFactoryManager::getInstance()->getFactory(type);
	//PtrWidget Widget = Factory->create(nom);
	//
	//registerWidget(Widget, etat); 

	//return Widget;
	return WidgetsManager::getInstance()->createWidget(type, name);
	//PtrWidget widget = WidgetsManager::getInstance()->createWidget(type, nom);
	//widget->setFonte(Gfx->getDefaultFont());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget GuiManager::reloadWidget(const std::string& type, const std::string& name)
{
	//PtrWidgetsFactory Factory = WidgetsFactoryManager::getInstance()->getFactory(type);
	//PtrWidget Widget = Factory->create(nom);
	//
	//registerWidget(Widget, etat); 

	//return Widget;
	PtrWidget widget = WidgetsManager::getInstance()->getWidget<BaseWidget>(name);
	WidgetsManager::getInstance()->affectLook(widget, type);
	return widget;
	//PtrWidget widget = WidgetsManager::getInstance()->createWidget(type, nom);
	//widget->setFonte(Gfx->getDefaultFont());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::cleanDelayed()
{
	std::vector<PtrWidget> vec = getRootWidget()->getChildren();
	for(unsigned int i = 0; i < vec.size(); i++)
	{
		vec[i]->destroy();
	}
	//std::vector<PtrWidget> vec = WidgetsManager::getInstance()->getAllWidgets();
	//for(int i = 0; i < vec.size(); i++)
	//{
	//	vec[i]->destroy();
	//}

	//getRootWidget()->removeChildren();
	myFocusWidgetManager->clean();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::clean()
{
	WidgetsManager::getInstance()->clean();
	getRootWidget()->removeChildren();
	myFocusWidgetManager->clean();
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool GuiManager::processEvent(BaseInput& ev)
{
	ev.process();

	//Boolean to know if the gui managed the event, and doesn't want it to be 
	//reused
	bool result = false;

	std::queue<KeyboardEvent>& keyEvents = BaseInput::getKeyboardEv();
	std::queue<MouseEvent>& mouseEvents = BaseInput::getMouseEv();

	while(!keyEvents.empty())
	{
		KeyboardEvent ev = keyEvents.front();
		if(handleKeyboardEvent(ev))
			result = true;
		keyEvents.pop();
	}
	while(!mouseEvents.empty())
	{
		MouseEvent ev = mouseEvents.front();
		if(ev.type == Event::MOUSE_MOVE ||
		   ev.type == Event::MOUSE_RELEASED ||
		   ev.type == Event::MOUSE_PRESSED)
		{
			myMousePosition = Point(ev.myX, ev.myY);
		}
		
		if(myMouseClickAnalyzer.updateDoubleClick(ev, myMousePosition)) //Remove Singleton
		{
			if(handleMouseEvent(ev, myMousePosition))
				result = true;
		}
		mouseEvents.pop();
	}

	return result;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool GuiManager::handleKeyboardEvent(KeyboardEvent& ev)
{
	if(!getRootWidget()->isVisible())
		return false;

	myKeyRepeatManager.newKeyboardEvent(ev);

	bool resultat = false;

	PtrWidget cible = getRootWidget()->getFocusedChild();

	if(cible)// && notModal
	{
		ev.myWidget = cible.get();

		if(ev.type == Event::KEY_PRESSED)
		{
			//if(!myIsKeyPressed)
			//{
			//	myInitialKeyRepeatTime = 0;
			//	myKeyRepeatTime = 0;
			//	//myLastKeyPressedEvent = ev;
			//	myIsKeyPressed = true;
			//}

			if(cible->handleKeyPressed(ev))
				resultat = true;
		}
		else if(ev.type == Event::KEY_RELEASED)
		{
			myIsKeyPressed = false;

			if(cible->handleKeyReleased(ev))
				resultat = true;
		}
		else if(ev.type == Event::TEXT_ENTERED)
		{
			myLastKeyPressedEvent = ev;
			if(cible->handleTextEntered(ev))
				resultat = true;
		}
	}

	return resultat;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool GuiManager::handleMouseEvent(MouseEvent& ev, const Point& mousePos)
{
	bool resultat = false;

	PtrWidget target = getWidgetCaughtInput();
	if(target && target->areEventsPropagatedToChildren())
	{
		Point coords = target->convertToMyCoordinates(mousePos);
		PtrWidget tmp = target->getChildAt(coords.x + target->getX(), coords.y + target->getY());
		if(tmp)
		{
			target = tmp;
		}
	}
	
	if(!target)
	{
		//Recursive function looking for the last child
		PtrWidget tmp = getWidgetAt(mousePos);
		if(tmp)
			target = tmp;
	}

	if(!target)
		return false;

	if(getWidgetModal() && target != getWidgetModal())
	{
		if(!target->isDescendantFrom(getWidgetModal()))
			target = getWidgetModal();
	}

	if(target->mustBeDestroyed())
		return false;

	Point coords = target->convertToMyCoordinates(mousePos);

	ev.myX = coords.x;
	ev.myY = coords.y;
	ev.myWidget = target.get();
	//MouseEvent Se(cible.get(), 
	//	coords.x, 
	//	coords.y, 
	//	ev.Type == sf::Event::MouseWheelMoved ? ev.MouseWheel.Delta : 0.f,
	//	ev.MouseButton.Button);

	if(ev.type == Event::MOUSE_PRESSED)
	{
		if(myMouseClickAnalyzer.isDoubleClick() && 
			target->isDoubleClickEnabled())
		{
			if(target->handleDoubleClick(ev))
				resultat = true;

			myMouseClickAnalyzer.setDoubleClickHandled(true);
		}
		else if((!myMouseClickAnalyzer.isDoubleClick() 
				&& myMouseClickAnalyzer.okPourClic())
				|| !target->isDoubleClickEnabled())
		{
			if(target->handleMousePressed(ev))
				resultat = true;

			if(myMouseClickAnalyzer.isDoubleClick())
				myMouseClickAnalyzer.setDoubleClickHandled(false);
		}
	}
	else if(ev.type == Event::MOUSE_RELEASED)
	{
		//std::cout << "ok" << std::endl;
		if(target->handleMouseReleased(ev))
			resultat = true;
	}
	else if(ev.type == Event::MOUSE_MOVE)
	{
		updateWidgetsContainingMouse(mousePos); //Should we move this ?
		if(target->handleMouseHover(ev))
			resultat = true;
	}
	else if(ev.type == Event::MOUSE_WHEEL)
	{
		if(target->handleMouseWheel(ev))
			resultat = true;
	}

	return resultat;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::updateWidgetsContainingMouse(const Point& mousePos)
{
	std::vector<PtrWidget> widgets = getWidgetsAt(mousePos);
	std::vector<WeakPtrWidget> weakWidgets;
	weakWidgets.assign(widgets.begin(), widgets.end());
	
	auto comparator = [] (WeakPtrWidget left, WeakPtrWidget right) -> bool { return left.lock().get() < right.lock().get(); };

	//std::sort(widgets.begin(), widgets.end());
	std::sort(weakWidgets.begin(), weakWidgets.end(), comparator);

	//std::vector<PtrWidget> widgetEntered;
	//std::vector<PtrWidget> widgetsExited;
	std::vector<WeakPtrWidget> widgetsEntered;
	std::vector<WeakPtrWidget> widgetsExited;
	std::set_difference(weakWidgets.begin(), 
		weakWidgets.end(), 
		myHoveredWidgets.begin(), 
		myHoveredWidgets.end(), 
		std::inserter(widgetsEntered, widgetsEntered.begin()),
		comparator);
	
	std::set_difference(myHoveredWidgets.begin(), 
		myHoveredWidgets.end(),
		weakWidgets.begin(), 
		weakWidgets.end(), 
		std::inserter(widgetsExited, widgetsExited.begin()),
		comparator);
	//std::set_difference(widgets.begin(), 
	//	widgets.end(), 
	//	myHoveredWidgets.begin(), 
	//	myHoveredWidgets.end(), 
	//	std::inserter(widgetsEntered, widgetsEntered.begin()));
	
	//std::set_difference(myHoveredWidgets.begin(), 
	//	myHoveredWidgets.end(),
	//	widgets.begin(), 
	//	widgets.end(), 
	//	std::inserter(widgetsExited, widgetsExited.begin()));

	myHoveredWidgets.clear();
	//myHoveredWidgets = widgets;
	myHoveredWidgets = weakWidgets;

	std::vector<WeakPtrWidget>::iterator it = widgetsEntered.begin();
	for(; it != widgetsEntered.end();)
	{
		PtrWidget tmpEntered = it->lock();
		if(tmpEntered)
		{
			tmpEntered->onWidgetEntered();
			++it;
		}
		else
			it = widgetsEntered.erase(it);
	}

	it = widgetsExited.begin();
	for(; it != widgetsExited.end();)
	{
		PtrWidget tmpExited = it->lock();
		if(tmpExited)
		{
			tmpExited->onWidgetExited();
			++it;
		}
		else
			it = widgetsExited.erase(it);
	}

	//std::vector<PtrWidget>::iterator it = widgetEntered.begin();
	//for(; it != widgetEntered.end(); ++it)
	//{
	//	(*it)->onWidgetEntered();
	//}

	//it = widgetsExited.begin();
	//for(; it != widgetsExited.end(); ++it)
	//{
	//	(*it)->onWidgetExited();
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget GuiManager::getWidgetAt(const Point& mousePos)
{
	return getWidgetAt(mousePos.x, mousePos.y);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget GuiManager::getWidgetAt(int x, int y)
{
	if(!getRootWidget()->isVisible())
		return PtrWidget();

	PtrWidget w = getRootWidget()->getChildAt(x, y);
	return w ? w : getRootWidget();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<PtrWidget> GuiManager::getWidgetsAt(const Point& posSouris)
{
	return getWidgetsAt(posSouris.x, posSouris.y);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<PtrWidget> GuiManager::getWidgetsAt(int x, int y)
{
	if(!getRootWidget()->isVisible())
		return std::vector<PtrWidget>();

	//return getRootWidget()->getChildrenAt(x, y);
	std::vector<PtrWidget> res = getRootWidget()->getChildrenAt(x, y);;
	res.push_back(getRootWidget());

	return res;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrDefaultContainer GuiManager::getRootWidget()
{
	if(myRootWidget == NULL)
	{
		myRootWidget = std::dynamic_pointer_cast<DefaultContainer>(
			createWidget("DefaultContainer", "_RootWidget"));
		myRootWidget->setDimensions(0, 0, getWindowWidth(), getWindowHeight());
		myRootWidget->setGraphics(myGraphics);
		myRootWidget->affectFocusWidgetManager(myFocusWidgetManager);
	}

	return myRootWidget;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::setWindowSize(int width, int height)//, float ratioX, float ratioY)
{
	myWidth = width;
	myHeight = height;

	//myRatioX = ratioX;
	//myRatioY = ratioY;

	if(myGraphics)
		myGraphics->assignWindowSize(getWindowWidth(), getWindowHeight());
	getRootWidget()->setDimensions(0, 0, width, height);
}	

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::setGraphics(BaseGraphics* gfx) 
{
	if(gfx && myGraphics != gfx)
	{
		delete myGraphics; 
		myGraphics = gfx;
		myGraphics->assignWindowSize(getWindowWidth(), getWindowHeight());
		getRootWidget()->setGraphics(gfx);
	}
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void GuiManager::setWidgetCatchInputs(PtrWidget w)
//{
//	if(MonWidgetCaptureEntrees != w)
//	{
//		//if(MonWidgetCaptureEntrees)
//			//MonWidgetCaptureEntrees->onCapturePerdue();
//		MonWidgetCaptureEntrees = w;
//		//MonWidgetCaptureEntrees->onCaptureGagnee();
//	}
//		
//	//MonWidgetModal = getWidget<BaseWidget>(w->getName());
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget GuiManager::getWidgetCaughtInput()
{
	return myFocusWidgetManager->getWidgetCaughtInput();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget GuiManager::getWidgetModal()
{
	return myFocusWidgetManager->getWidgetModal();
	//return MonWidgetModal.empty() ? PtrWidget() : MonWidgetModal.top()->isVisible() ? MonWidgetModal.top() : PtrWidget();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double GuiManager::getRatioX() const
{
	const double EPSILON = 1e-10;
	return getWindowWidth() / 
			(WidgetLookManager::getInstance()->getPreferredX() + EPSILON);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double GuiManager::getRatioY() const
{
	const double EPSILON = 1e-10;
	return getWindowHeight() / 
			(WidgetLookManager::getInstance()->getPreferredY() + EPSILON);
}

////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void GuiManager::setWidgetModal(PtrWidget w) //Utile ?
//{
//	//myFocusWidgetManager->setWidgetModal(w);
//	//if(w)
//	//{
//	//	MonWidgetModal.push(w);
//	//}
//}
//
////=============================================================================
/////////////////////////////////////////////////////////////////////////////////
//void GuiManager::relacherWidgetModal(PtrWidget w)
//{
//	//assert(MonWidgetModal.top() == w && 
//	//	"On ne peut relacher la modalité que du widget de tête");
//
//	if(!MonWidgetModal.empty() && w == MonWidgetModal.top())
//	{
//		MonWidgetModal.pop();
//	}
//}

//void GuiManager::manageKeyRepeat(unsigned int elapsedTime)
//{
//	if(!isKeyRepeatEnabled() || !myIsKeyPressed)
//		return;
//
//	if(myInitialKeyRepeatTime < TIME_OUT_REPEAT_FIRST)
//	{
//		myInitialKeyRepeatTime += elapsedTime;
//		if(myInitialKeyRepeatTime >= TIME_OUT_REPEAT_FIRST)
//		{
//			//add the difference
//			myKeyRepeatTime += elapsedTime - (myInitialKeyRepeatTime - TIME_OUT_REPEAT_FIRST);
//			myInitialKeyRepeatTime = TIME_OUT_REPEAT_FIRST;
//		}
//	}
//	else
//	{
//		myKeyRepeatTime += elapsedTime;
//	}
//
//	if(myInitialKeyRepeatTime >= TIME_OUT_REPEAT_FIRST && 
//	   myKeyRepeatTime >= TIME_OUT_REPEAT)
//	{
//		KeyboardEvent ev = myLastKeyPressedEvent;
//		handleKeyboardEvent(ev);
//		myKeyRepeatTime = 0;
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::update(unsigned int elapsedTime)
{
	if(isKeyRepeatEnabled())
		myKeyRepeatManager.manageKeyRepeat(elapsedTime);
		//manageKeyRepeat(elapsedTime);

	getRootWidget()->update(elapsedTime);

	myFocusWidgetManager->update();
	WidgetsManager::getInstance()->removeDestructedWidgets();
	WidgetsManager::getInstance()->removeUniqueWidgets();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiManager::draw()
{
	myGraphics->beginDraw();

	//myGraphics->assignWindowSize(getWindowWidth(), getWindowHeight());
	if((myGraphics->isOptimizedDrawing() && myGraphics->isInvalidated()) || !myGraphics->isOptimizedDrawing())
	{
		if(getRootWidget()->isVisible())
			getRootWidget()->draw();
		//myGraphics->myInvalidate = false;
	}

	if(myGraphics->isOptimizedDrawing())
	{
		myGraphics->drawOptimized();
	}

	myGraphics->endDraw();
}

} //end namespace

//Ok. PropertySystem statique dans baseWidget. Une map<string, map<string, prop> > pour la liste des props par widget//////////////////
//Ok.Vérifier la suppression et la destruction des widgets dans le widgets manager lorsqu'on les enlève de leur parent///////////////////
//Ok. Ajouter le mode Lecture seule
//Ok. Coords relatives et absolues
//Ok. Translation coords du gfx
//Ok. Ajouter TexteChanged à la textbox
//Ok. Mixer TextField et textbox
//Ok. Intégrer un focusManager
//capturerEntrées ne doit pas donner le focus (mais ce dernier doit être récupéré avant normalement)
//Ok. Renommer les classes IXxxx en BaseXxxx si nécessaire
//Vérifier si on peut déplacer le chargement du LookNFeel
//Ok. Mettre les includes dans leur propre répertoire
//Ok. Vérifier les refs sur std::function
// Ok. virtual getChildAt ?
// Ok. binding de fonction : instance* = NULL ? pour fonctions libres
// WidgetLook ajouter nom de l'enfant pour le renderer enfant
// Ok. StaticImage -> Imagebox
// Supprimer les \n dans le insert de la textbox
// Ok ? Textbox -> -amount à corriger
// ImageSheetManager : Renvoyer une copie de l'image, au lieu d'un pointeur ?
// Ok. Positionnement relatif des zones XML
// Ok. Reconfigurer la scrollbar lors du redimensionnement du TextField.
// ScreenDep à faire
// Ok. XML : layout = "true"
// Enum key codes
//Ok. updateWidgetContainingMouse+exited+widgets supprimés
//Homogénéité des noms TextBox, etc...
//
//
//
//jpgi::basewidget
//{
//	virtual ajouterProp(...) = 0;
//	virtual setProp(...) = 0;
//	...
//};
//
//template<class T>
//gaia::crtpWidget<T> : public BaseWidget
//{
//	virtual ajouterProp(...)
//	{
//		SystemeProp.ajouter(T::typeWidget, nom, prop);
//	}
//};
//Sinon (bidouille) définir une variable privée int monPrivTypeWidget = myWidgetType; //quand l'initialiser ?
//class BaseWidget
//{
//	ajouterProp(...)
//	{
//		SystemeProp.ajouter(monPrivTypeWidget, nom, prop);
//	}

//class FocusWidgetManager
//{
//public:
//	void setWidgetCatchInputs(PtrWidget w)
//	{
//		if(MonWidgetCaptureEntrees != w)
//		{
//			//if(MonWidgetCaptureEntrees)
//				//MonWidgetCaptureEntrees->onCapturePerdue();
//			MonWidgetCaptureEntrees = w;
//			//MonWidgetCaptureEntrees->onCaptureGagnee();
//		}
//		
//		//MonWidgetModal = getWidget<BaseWidget>(w->getName());
//	}
//
//	PtrWidget getWidgetCaughtInput()
//	{
//		return MonWidgetCaptureEntrees;
//	}
//
//	PtrWidget getWidgetModal()
//	{
//		//if(mesWidgetsModaux.empty())
//		//	return PtrWidget();
//		for(unsigned int i = mesWidgetsModaux.size() - 1; i >= 0; i--)
//		{
//			if(mesWidgetsModaux[i]->isVisible())
//				return mesWidgetsModaux[i];
//		}
//
//		return PtrWidget();
//		//return MonWidgetModal.empty() ? PtrWidget() : MonWidgetModal.top()->isVisible() ? MonWidgetModal.top() : PtrWidget();
//	}
//
//	void ajouterWidgetModal(PtrWidget w)
//	{
//		if(w)
//		{
//			for(unsigned int i = 0; i < mesWidgetsModaux.size(); i++)
//			{
//				if(mesWidgetsModaux[i] == w)
//					return;
//			}
//
//			mesWidgetsModaux.push_back(w);
//		}
//	}
//
//	void relacherWidgetModal(PtrWidget w)
//	{
//		//assert(MonWidgetModal.top() == w && 
//		//	"On ne peut relacher la modalité que du widget de tête");
//
//		if(!mesWidgetsModaux.empty() && w == mesWidgetsModaux.back())
//		{
//			mesWidgetsModaux.pop_back();
//		}
//	}
//
//protected:
//	PtrWidget MonWidgetCaptureEntrees;
//	std::deque<PtrWidget> mesWidgetsModaux;
//	//std::weak_ptr<
//};
//
//
//class Window : public BaseWidget
//{
//public:
//	PtrFrameBar getFrameBar();
//
//protected:
//	///////////////////////////////////////////////////////////////////////////////
//	/// \brief Can be overriden by children. Handles in a generic way the response to a 
//	/// mouse event.
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleMousePressed_impl(MouseEvent& ev)
//	{
//		myIsResizing = true;
//	}
//
//	//////////////////////////////////////////////////////////////////////////////
//	/// \brief Can be overriden by children. Handles in a generic way the response to a 
//	/// mouse event.
//	///////////////////////////////////////////////////////////////////////////////
//	virtual bool handleMouseHover_impl(MouseEvent& ev)
//	{
//		if(myIsResizing)
//		{
//			//setDimensions(getX(), getY(), 
//		}
//	}
//};
//
//GAIA_REGISTER_TYPE(Window)
//
//if(parent == root)
// createSurface()
// Vérifier isDescendantFrom