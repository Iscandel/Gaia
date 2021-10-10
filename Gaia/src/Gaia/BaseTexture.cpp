#include "Gaia/BaseTexture.h"
#include "Gaia/BaseImageLoader.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
std::shared_ptr<BaseImageLoader> BaseTexture::myImageLoader;// = NULL;

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseTexture::BaseTexture()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BaseTexture::~BaseTexture(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BaseTexture::setLoader(BaseImageLoader* loader)
{
	//if(monImageLoader) 
	//	delete monImageLoader;
	
	myImageLoader.reset(loader);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
PtrTexture BaseTexture::load(const std::string& path)
{
	if(!myImageLoader)
		throw GuiException("No image loader set.");

	return myImageLoader->load(path);
}

} //end namespace