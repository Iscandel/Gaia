///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/WidgetManager.h"
#include "Gaia/WidgetFactoryManager.h"
#include "Gaia/WidgetLookManager.h"

#include "Gaia/widgets/WidgetStaticType.h"

#include "Gaia/tools/Tools.h"

namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidget WidgetsManager::createWidget(const std::string& type, const std::string& name)
{
	std::string finalName = name;

	if(name == "")
		finalName = generateUniqueName();

	//WidgetLook* look = WidgetLooksManager::getInstance()->getLook(type);

	//if(look)
	//	look->initEnfants(nomFinal);

	//Widget creation
	PtrWidgetFactory Factory = WidgetFactoryManager::getInstance()->getFactory(type);
	PtrWidget widget = Factory->create(finalName);
	
	affectLook(widget, type);
	////Widget look and renderer
	//WidgetLook* look = WidgetLookManager::getInstance()->getLook(type);

	////if the widget has no look&feel, try to find a parent's one
	//std::string tmpType = type;
	//while(!look && tmpType != "")
	//{
	//	tmpType = gaia::priv::getParentType(tmpType);
	//	look = WidgetLookManager::getInstance()->getLook(tmpType);
	//}

	////We assign a renderer to the widget and its children
	//if(look)
	//	look->initWidget(widget);

	if(registerWidget(widget))
		return widget;
	else
		return PtrWidget();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetsManager::affectLook(PtrWidget widget, const std::string& type)
{
	//Widget look and renderer
	WidgetLook* look = WidgetLookManager::getInstance()->getLook(type);

	//if the widget has no look&feel, try to find a parent's one
	std::string tmpType = type;
	while(!look && tmpType != "")
	{
		tmpType = gaia::priv::getParentType(tmpType);
		look = WidgetLookManager::getInstance()->getLook(tmpType);
	}

	//We assign a renderer to the widget and its children
	if(look)
		look->initWidget(widget);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool WidgetsManager::registerWidget(PtrWidget w) 
{
	std::map<std::string, PtrWidget>::iterator it = myWidgets.find(w->getName());

	if(it == myWidgets.end())
	{
		myWidgets[w->getName()] = w;
		return true;
	}
	else if(w != it->second)
	{
		ILogger::log(ILogger::ERRORS) << "Widget with the same name and " 
			"different already exists :" << w ->getName() << ". Cannot register\n";

		return false;
	}

	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetsManager::clean()
{
	myWidgets.clear();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<PtrWidget> WidgetsManager::getAllWidgets()
{
	std::vector<std::shared_ptr<BaseWidget> > vec;

	std::map<std::string, PtrWidget>::iterator it = myWidgets.begin();
	for(;it != myWidgets.end(); ++it)
	{
		vec.push_back(it->second);
	}

	return vec;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetsManager::removeDestructedWidgets()
{
	std::map<std::string, PtrWidget>::iterator it = myWidgets.begin();
	for(;it != myWidgets.end();)
	{
		if(it->second->mustBeDestroyed())
		{
			std::map<std::string, PtrWidget>::iterator tmp = it;
			++it;
			myWidgets.erase(tmp);
		}
		else
		{
			++it;
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetsManager::removeUniqueWidgets()
{
	std::map<std::string, PtrWidget>::iterator it = myWidgets.begin();
	for(;it != myWidgets.end();)
	{
		if(it->second.unique())
		{
			std::map<std::string, PtrWidget>::iterator tmp = it;
			++it;
			tmp->second->destroy();
			myWidgets.erase(tmp);
		}
		else
		{
			++it;
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool WidgetsManager::removeWidget(const std::string& name)
{
	std::map<std::string, PtrWidget>::iterator it = myWidgets.find(name);
	if(it != myWidgets.end())
	{
		it->second->destroy();
		myWidgets.erase(it);
		return true;
	}

	return false;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool WidgetsManager::removeWidget(PtrWidget w)
{
	return removeWidget(w->getName());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::string WidgetsManager::generateUniqueName()
{
	static int numWidget = 0;
	return "_UniqueName" + tools::numToString(++numWidget);
}

} //end namespace