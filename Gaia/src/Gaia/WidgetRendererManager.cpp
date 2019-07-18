///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/WidgetRendererManager.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
IWidgetRenderer* WidgetRendererManager::createRenderer(
									const std::string& rendererName, 
									PtrWidget target)
{
	RendererList::iterator it = myRenderers.find(rendererName);

	if(it == myRenderers.end())
		throw GuiException("WidgetRendererFactory " + rendererName + " not found");

	PtrWidgetRendererFactory factory = it->second;

	if(it != myRenderers.end())
		return factory->create(target);

	return NULL;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetRendererManager::addWidgetRenderer(const std::string& rendererName, 
											  PtrWidgetRendererFactory factory)
{
	RendererList::iterator it = myRenderers.find(rendererName);

	if(it != myRenderers.end())
		throw GuiException("Renderer " + rendererName + " already exists");

	myRenderers[rendererName] = factory;
}

} //end namespace