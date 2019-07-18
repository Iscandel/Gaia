#ifndef H__SFMLFONT__130620112052__H
#define H__SFMLFONT__130620112052__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLConfig.h"
#include "Gaia/BaseFont.h"
#include "Gaia/BaseGraphics.h"

#include <SDL/SDL_TTF.h>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief Class for manipulating SFML font.
///////////////////////////////////////////////////////////////////////////////
class GAIA_SDL_DLL SDLFont : public BaseFont
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////////
	SDLFont(void);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param path : Path to the font file to use.
	/// \param charSize : Height of a character.
	///////////////////////////////////////////////////////////////////////////////
	SDLFont(const std::string& path, int charSize);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	/// 
	/// \param font : Pointer to the SDL font to use. This class destroys the
	/// font when it changes, or in the destructor.
	///////////////////////////////////////////////////////////////////////////
	SDLFont(TTF_Font* font);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	/// 
	/// \param font : Pointer to the SDL font resource to use. Freeing of the 
	/// is managed by this class.
	/// \param characterHeight : Height of a character.
	///////////////////////////////////////////////////////////////////////////
	//SDLFont(::SDL_RWops* fontResource, int characterHeight);
	SDLFont::SDLFont(char* buffer, std::streamsize length, int characterHeight);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Destructor.
	///////////////////////////////////////////////////////////////////////////////
	~SDLFont(void);

	//@override
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Draws a string.
	///
	/// You shouldn't call this function directly. Use the graphics renderer instead.
	///
	/// \param graphics : The graphics rendering object.
	/// \param text : Text to draw.
	/// \param x : Top left corner.
	/// \param y : Top left corner.
	/// \param col : Text color.
	/// \param charHeight : Height of the chars to display.
	///
	///////////////////////////////////////////////////////////////////////////////
	virtual void drawText(BaseGraphics* graphics, 
						  const std::string& text, 
						  int x, 
						  int y, 
						  const Color& col, 
						  unsigned int charHeight);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Assigns a new SDL font.
	///
	/// \param path : Path to the font.
	/// \param charSize : Character height.
	///////////////////////////////////////////////////////////////////////////////
	void setFont(const std::string& path, int charSize);
	
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Computes the width of a given string, with a given character heigth.
	///
	/// \param text : Text for which we need the width.
	/// \param charHeight : Height of the character.
	///
	/// \return The text width.
	///////////////////////////////////////////////////////////////////////////////
	float getTextWidth(const std::string& text, unsigned int height);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Computes the height of a given string, with a given character heigth.
	///
	/// \param text : Text for which we need the height.
	/// \param charHeight : Height of the character.
	///
	/// \return The text height.
	///////////////////////////////////////////////////////////////////////////////
	virtual float getTextHeight(const std::string& text, unsigned int charHeight);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the contained SDL font.
	///
	/// \return The encapsulated font.
	///////////////////////////////////////////////////////////////////////////////
	const TTF_Font& getSFMLFont() const {return *myFont;}

	//static const char myDefaultData[];

//protected:
//	static const char*

protected:
	TTF_Font* myFont; ///< Pointer to the SDL font.
	SDL_Surface* myString; ///< Visual string used to draw text.
	std::string myPath;
	char* myFontBuffer;
	std::streamsize myBufferLength;
	::SDL_RWops* myFontResource;
};

//const char SDLFont::myDefaultData[] = 
//{
//#include "Arial.h"
//};

/// Smart pointer to SDLFont.
typedef boost::shared_ptr<SDLFont> PtrSDLFont;

} //end namespace

#endif