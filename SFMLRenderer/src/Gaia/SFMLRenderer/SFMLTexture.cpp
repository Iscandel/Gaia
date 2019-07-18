///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SFMLRenderer/SFMLTexture.h"

namespace gaia
{
SFMLTexture::SFMLTexture(sf::Texture* img)
:myImage(img)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SFMLTexture::~SFMLTexture(void)
{
	delete myImage;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLTexture::setSmooth(bool smooth)
{
	myImage->setSmooth(smooth);
}

} //end namespace