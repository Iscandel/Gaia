#include "Gaia/widgetRenderers/WidgetRenderer.h"

namespace gaia
{
IWidgetRenderer::IWidgetRenderer(void)
:myMustClip(true)
,myFixedClippingArea(false)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
IWidgetRenderer::~IWidgetRenderer(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void IWidgetRenderer::addImage(const std::string& stateName, const Image& image)
{
	//If the key is not empty
	if(stateName != "")
	{
		//If the same key already exists
		if(myImages.find(stateName) != myImages.end())
		{
			//If the image contains a NULL texture, we delete the key. It means
			//we don't want to draw anything for this key.
			if(image.getTexture() == NULL)
			{
				myImages.erase(stateName);
			}
			else //replace the existing one
			{
				myImages[stateName] = image;
			}
		}
		else
		{
			if(image.getTexture() != NULL)
			{
				myImages.insert(std::make_pair(stateName, image));
			}
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool IWidgetRenderer::imageExists(const std::string& state)
{
	return myImages.find(state) != myImages.end();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void IWidgetRenderer::deleteImage(const std::string& stateName)
{
	if(myImages.find(stateName) != myImages.end())
	{
		myImages.erase(stateName);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Image& IWidgetRenderer::getImage(const std::string& stateName)
{
	ImageList::iterator it = myImages.find(stateName);

	if(it == myImages.end())
		throw GuiException("Image with state " + stateName + " not found in the renderer");

	return it->second;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void IWidgetRenderer::addArea(const std::string& areaName, const Rect<double>& rect)
//{
//	if(areaName != "")
//		myAreas[areaName] = rect;
//}

void IWidgetRenderer::addLayoutArea(const std::string& areaName, const LayoutInfos& infos)
{
	myLayoutAreas[areaName] = infos;
	myLayoutAreas[areaName].setLayoutTypeIsArea(true);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void IWidgetRenderer::deleteArea(const std::string& areaName)
{
	if(myAreas.find(areaName) != myAreas.end())
	{
		myAreas.erase(areaName);
	}
}

} //end namespace