///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/WidgetLookManager.h"

//#include "Gaia/WidgetLook.h"

namespace gaia
{
WidgetLook* WidgetLookManager::getLook(const std::string& widgetName)
{
	std::map<std::string, WidgetLook>::iterator it = myLooks.find(widgetName);

	if(it != myLooks.end())
		return &it->second;

	return NULL;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLookManager::addLook(const std::string& widgetName, const WidgetLook& look)
{
	std::map<std::string, WidgetLook>::iterator it = myLooks.find(widgetName);

	if(it != myLooks.end())
		throw GuiException("Look for " + widgetName + " already exists");

	myLooks[widgetName] = look;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLookManager::clearLooks()
{
	myLooks.clear();
}

} //end namespace