///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/ImageSheet.h"

namespace gaia
{
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ImageSheet::ImageSheet(const std::string& path, const std::string& name)
:myName(name)
{
	if(path != "")
		myTexture = BaseTexture::load(path);
}

ImageSheet::ImageSheet(PtrTexture tex, const std::string& name)
:myName(name)
{
	myTexture = tex;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ImageSheet::~ImageSheet(void)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageSheet::loadTexture(const std::string& path)
{
	if(path != "")
		myTexture = BaseTexture::load(path);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ImageSheet::addImage(const std::string& name, const gaia::IntRect& dest)
{
	std::map<std::string, Image>::iterator it = myImages.find(name);
	if(it != myImages.end())
		throw gaia::GuiException("Image already exists in image sheet " + getName());

	myImages[name] = Image(myTexture, name, dest);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Image* ImageSheet::getImage(const std::string& name)
{
	std::map<std::string, Image>::iterator it = myImages.find(name);
	if(it != myImages.end()) 
		return &it->second;
	return NULL;
}

} //end namespace