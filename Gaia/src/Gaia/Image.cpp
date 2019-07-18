///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Image.h"

namespace gaia
{
Image::Image(PtrTexture texture, const std::string& name, const IntRect& dest)
		:myTexture(texture)
		,myName(name)
		,myDestination(dest)
{
		if(dest.width < 0 || dest.height < 0)
		{
			myDestination.x = 0; myDestination.y = 0;
			myDestination.width = myTexture ? myTexture->getWidth() : 0;
			myDestination.height = myTexture ? myTexture->getHeight() : 0;
		}
}

Image::~Image(void)
{
}

} // end namespace