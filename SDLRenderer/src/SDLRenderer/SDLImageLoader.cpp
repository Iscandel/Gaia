///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLImageLoader.h"
#include "Gaia/SDLRenderer/SDLTexture.h"
#include "Gaia/tools/Logger.h"

#include <SDL/SDL_image.h>
namespace gaia
{
PtrTexture SDLImageLoader::load(const std::string& path)
{
	SDL_Surface* surface = ::IMG_Load(path.c_str());
	
	if(!surface)
	{
		ILogger::log(ILogger::ERRORS) << "Image " << path << " cannot be loaded\n";
	}
	else
	{
		SDL_Surface* tmpSurface = surface;
		surface = ::SDL_DisplayFormatAlpha(surface);
		::SDL_FreeSurface(tmpSurface);
	}

	PtrSDLTexture img(new SDLTexture(surface));

	return img;
}

} //end namespace