///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/WidgetFactoryManager.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFactoryManager::addFactory(PtrWidgetFactory factory) 
{
	FactoryMap::iterator it = myFactories.find(factory->getWidgetType());
	
	if(factory->getWidgetType() == "" )
	{
		throw GuiException("No specified type for the widget");
	}

	if(it != myFactories.end())
	{
		throw GuiException("Widget " + factory->getWidgetType() + " has already been registered");
	}

	myFactories.insert(std::make_pair(factory->getWidgetType(), factory));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetFactoryManager::removeFactory(const std::string& type)
{
	FactoryMap::iterator it = myFactories.find(type);
	if(it != myFactories.end())
	{
		myFactories.erase(type);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrWidgetFactory WidgetFactoryManager::getFactory(const std::string& type)
{
	FactoryMap::iterator it = myFactories.find(type);
	if(it != myFactories.end())
	{
		return it->second;
	}
	else
	{
		throw GuiException(std::string("The requested factory " + type + " doesn't exist"));
	}
}

} //end namespace