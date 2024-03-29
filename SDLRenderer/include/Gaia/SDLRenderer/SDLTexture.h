#ifndef H__SFMLTEXTURE__H
#define H__SFMLTEXTURE__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLConfig.h"
#include "Gaia/BaseTexture.h"

#include <SDL/SDL.h>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief SFML implementation of the Texture class.
///////////////////////////////////////////////////////////////////////////////
class GAIA_SDL_DLL SDLTexture : public gaia::BaseTexture
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param image : Pointer to the underlying SDL image. This image is 
	/// destroyed when this SDL texture is destroyed.
	///////////////////////////////////////////////////////////////////////////////
	SDLTexture(SDL_Surface* image);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Destructor.
	///////////////////////////////////////////////////////////////////////////////
	~SDLTexture(void);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the texture height.
	///
	///	\return The height.
	///////////////////////////////////////////////////////////////////////////////
	int getHeight() const {return myImage->h;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the texture width.
	///
	///	\return The width.
	///////////////////////////////////////////////////////////////////////////////
	int getWidth() const {return myImage->w;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the underlying SDL image.
	///
	///	\return The contained SDL image.
	///////////////////////////////////////////////////////////////////////////////
	SDL_Surface& getSDLImage() {return *myImage;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Direct conversion to an SDL_Surface.
	///////////////////////////////////////////////////////////////////////////////
	operator SDL_Surface& () {return *myImage;}

protected:
	SDL_Surface* myImage;
};

///Smart pointer to an SDL texture
typedef boost::shared_ptr<SDLTexture> PtrSDLTexture; 

} //end namespace

#endif