///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SFMLRenderer/SFMLImageLoader.h"
#include "Gaia/SFMLRenderer/SFMLTexture.h"
#include "Gaia/tools/Logger.h"

#include <SFML/Graphics.hpp>

namespace gaia
{
SFMLImageLoader::SFMLImageLoader(bool smooth)
:mySmooth(smooth)
{
}

///////////////////////////////////////////////////////////////////////////////
//=============================================================================
PtrTexture SFMLImageLoader::load(const std::string& path)
{
	sf::Texture* sfImg = new sf::Texture;
	if(!sfImg->loadFromFile(path))
	{
		ILogger::log(ILogger::ERRORS) << "Image " << path << " cannot be loaded\n";
	}

	sfImg->setSmooth(mySmooth);

	PtrSFMLTexture img(new SFMLTexture(sfImg));

	return img;
}

} //end namespace