#ifndef H__SFMLIMAGELOADER_180920110114__H
#define H__SFMLIMAGELOADER_180920110114__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLConfig.h"
#include "Gaia/BaseImageloader.h"

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief SFML implementation of the ImageLoader class.
///////////////////////////////////////////////////////////////////////////////
class GAIA_SDL_DLL SDLImageLoader : public gaia::BaseImageLoader
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Load a texture using the path name.
	///
	/// \param path : path of the file.
	///////////////////////////////////////////////////////////////////////////
	virtual PtrTexture load(const std::string& path);
};

} //end namespace

#endif