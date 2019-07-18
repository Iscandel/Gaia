///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/WidgetLook.h"

#include "Gaia/WidgetManager.h"
#include "Gaia/ImageSheetsManager.h"
#include "Gaia/WidgetRendererManager.h"

namespace gaia
{
WidgetLook::WidgetLook(void)
{
}

////Not used anymore
//void WidgetLook::initChilden(const std::string& widgetName)
//{
//	for(unsigned int i = 0; i < myChildNames.size(); i++)
//	{
//		std::string nom = myChildNames[i] + widgetName + "__";
//		WidgetsManager::getInstance()->createWidget(myChildTypes[i], widgetName);
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::initWidget(PtrWidget widget)
{
	init(widget, myRenderer, myImages, myLayoutAreas);

	for(unsigned int i = 0; i < myChildNames.size(); i++)
	{
		std::string name = myChildNames[i] + widget->getName();

		//PtrWidget w = WidgetsManager::getInstance()->createWidget(myChildTypes[i], name);

		//We retrieve the child
		PtrWidget w = WidgetsManager::getInstance()->getWidget<BaseWidget>(name);
	
		//w->setRelativeDimensions(myChildPositions[myChildNames[i]]);
		
		w->setLayoutInfos(getCloneLayoutInfos(myChildNames[i]));

		//We initialize the child
		init(w, 
			 myChildWidgetRenderer[i], 
			 myChildImages[myChildNames[i]], 
			 myChildLayoutAreas[myChildNames[i]]);

		//widget->add(w);//no need to add
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::init(PtrWidget w, 
					   const std::string& rendererName, 
					   const ImageByState& images, 
					   const LayoutAreaByName& areas)
{
	if(rendererName != "")
	{
		IWidgetRenderer* wr = WidgetRendererManager::getInstance()->createRenderer(rendererName, w);
		if(!wr)
		{
			throw GuiException("Widget renderer " + rendererName + 
			" not found in the WidgetRendererManager");
		}

		ImageByState::const_iterator it = images.begin();

		for(; it != images.end(); ++it)
		{
			Image* img = ImageSheetsManager::getInstance()->getImage(it->second.sheet, it->second.imageName);

			if(img)
			{
				wr->addImage(it->first, *img);
			}
			else
			{
				ILogger::log(ILogger::ERRORS) << "Image " << it->second.imageName 
					<< " not found in the sheet " + it->second.sheet << "\n";
			}
		}
		
		LayoutAreaByName::const_iterator itArea = areas.begin();

		for(; itArea != areas.end(); ++itArea)
		{
			wr->addLayoutArea(itArea->first, itArea->second);
		}

		w->setWidgetRenderer(wr);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::addImage(const std::string& stateName, 
						  const std::string& imageSheetName, 
						  const std::string& imageName)
{
	myImages.insert(std::make_pair(stateName, SheetImage(imageSheetName, imageName)));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::addLayoutArea(const std::string& areaName, const LayoutInfos& infos)//const Rect<double>& rect)
{
	myLayoutAreas.insert(std::make_pair(areaName, infos));
	//myAreas.insert(std::make_pair(areaName, rect));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::addChildImage(const std::string& name, 
							   const std::string& stateName, 
							   const std::string& imageSheetName, 
							   const std::string& imageName)
{
	myChildImages[name].insert(
		std::make_pair(stateName, SheetImage(imageSheetName, imageName)));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::addChildLayoutArea(const std::string& name, 
							  const std::string& areaName, 
							  const LayoutInfos& infos)
							  //const Rect<double>& rect)
{
	myChildLayoutAreas[name].insert(std::make_pair(areaName, infos));
	//myChildAreas[name].insert(std::make_pair(areaName, rect));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::addChild(const std::string& name, const std::string& type)
{
	if(name == "" || type == "")
	{
		throw GuiException("Widget name or type ( " + name + ", " + type + 
			" ) cannot be empty to initialize look.");
	}

	myChildNames.push_back(name);
	myChildTypes.push_back(type);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void WidgetLook::addChildPosition(const std::string& name, const Rect<double>& pos) 
//{
//	myChildPositions[name] = pos;
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WidgetLook::addChildWidgetRenderer(const std::string& rendererName) 
{
	myChildWidgetRenderer.push_back(rendererName);
}

void WidgetLook::addChildLayout(const std::string& name, const LayoutInfos& infos)
{
	myChildPositions[name] = infos;
}

PtrLayoutInfos WidgetLook::getCloneLayoutInfos(const std::string& name)
{
	PtrLayoutInfos res;

	std::map<std::string, LayoutInfos>::iterator it = myChildPositions.find(name);
	if(it != myChildPositions.end())
	{
		res = PtrLayoutInfos(new LayoutInfos(it->second));
	}

	return res;
}

} //end namespace