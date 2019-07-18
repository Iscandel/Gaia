///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLFont.h"
#include "Gaia/SDLRenderer/SDLGraphics.h"
#include "Gaia/SDLRenderer/SDLTools.h"
#include "Gaia/tools/Exceptions.h"

#include <iostream>
#include <fstream>

namespace gaia
{
SDLFont::SDLFont(void)
:myFont(NULL)
,myString(NULL)
,myFontBuffer(NULL)
,myBufferLength(0)
,myFontResource(NULL)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SDLFont::~SDLFont(void)
{
	TTF_CloseFont(myFont);
	::SDL_FreeRW(myFontResource);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SDLFont::SDLFont(const std::string& path, int charSize)
:myFont(NULL)
,myString(NULL)
,myFontBuffer(NULL)
,myBufferLength(0)
,myFontResource(NULL)
{
	setFont(path, charSize);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SDLFont::SDLFont(TTF_Font* font)
:myFont(NULL)
,myString(NULL)
,myFontBuffer(NULL)
,myBufferLength(0)
,myFontResource(NULL)
{
	if(!font)
	{
		throw GuiException("Null pointer to TTF_Font in SDLFont");
	}

	myFont = font;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//SDLFont::SDLFont(SDL_RWops* font, int characterHeight)
SDLFont::SDLFont(char* buffer, std::streamsize length, int characterHeight)
:myFont(NULL)
,myString(NULL)
,myFontBuffer(NULL)
,myBufferLength(0)
,myFontResource(NULL)
{
	myBufferLength = length;
	myFontBuffer = new char[myBufferLength];
	std::copy(buffer, buffer + myBufferLength, myFontBuffer);
	//myFontResource = font;
	myFontResource = ::SDL_RWFromConstMem(myFontBuffer, myBufferLength);
	myFont = TTF_OpenFontRW(myFontResource, 1, characterHeight);
}

//const char* SDLFont::getDefaultData() const
//{
//	static bool loaded = false;
//	if(!loaded)
//	{
//		const char SDLFont::myDefaultData[] = 
//		{
//			#include "Arial.h"
//		};
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLFont::setFont(const std::string& path, int charSize)
{
	TTF_CloseFont(myFont);

	std::ifstream file(path.c_str(), std::ifstream::in | std::ifstream::binary);
	 
	if(!file)
	{
		throw GuiException("Cannot load font : " + path);
		return;
	}
	// get length of file:
	file.seekg (0, std::ios::end);
	std::streamsize bufferLength = file.tellg();
	file.seekg (0, std::ios::beg);

	//::SDL_FreeRW(myFontResource);

	// allocate memory:
	delete[] myFontBuffer;
	myFontBuffer = new char[myBufferLength];
	//char* fontBuffer = new char[bufferLength];

	// read data as a block:
	file.read(myFontBuffer, myBufferLength);
	file.close();

	myFontResource = ::SDL_RWFromConstMem(myFontBuffer, myBufferLength);
	myFont = TTF_OpenFontRW(myFontResource, 1, charSize);
	
	//myFont = TTF_OpenFont(path.c_str(), charSize);
	//if(myFont)
	//{
	//	myPath = path;
	//}
	//else
	//{
	//	throw GuiException("Cannot load TTF_Font from : " + path + " in SDLFont");
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLFont::drawText(BaseGraphics* graphics, 
						const std::string& text, 
						int x, 
						int y, 
						const Color& col, 
						unsigned int characterHeight)
{
	//if(static_cast<int>(characterHeight) != ::TTF_FontHeight(myFont))
	//{
	//	std::cout << "Changing font" << std::endl;
	//	TTF_CloseFont(myFont);
	//	if(myFontResource != NULL)
	//	{
	//		myFontResource = ::SDL_RWFromConstMem(myFontBuffer, myBufferLength);
	//		myFont = TTF_OpenFontRW(myFontResource, 1, characterHeight);
	//		if(myFont == NULL)
	//		{
	//			std::cout << "ERR " << ::TTF_GetError();
	//		}
	//	}
	//	//TTF_CloseFont(myFont);

	//	//if(myPath != "")
	//	//{
	//	//
	//	//	myFont = TTF_OpenFont(myPath.c_str(), characterHeight);
	//	//}
	//	//else
	//	//{			
	//	//	std::cout << "Changing font" << std::endl;
	//	//		static const char defaultData[] = 
	//	//		{
	//	//			#include "Arial.h"
	//	//		};
	//
	//	//	SDL_RWops* resource =
	//	//		::SDL_RWFromConstMem(defaultData, sizeof(defaultData));

	//	//	myFont = TTF_OpenFontRW(resource, 1, characterHeight);
	//	//}
	//}

	SDL_FreeSurface(myString);
	myString = TTF_RenderText_Blended(myFont, text.c_str(), SDLTools::fromGuiColor(col));
	
	SDLGraphics* sdlGfx = static_cast<SDLGraphics*>(graphics);
	//assert(sfGfx);
	
	SDL_Surface* win = sdlGfx->getWindow();

	SDL_Rect position = sdlGfx->toSDLRect(IntRect(x, y, 0, 0));
    SDL_BlitSurface(myString, NULL, win, &position);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
float SDLFont::getTextWidth(const std::string& text, unsigned int height)
{
	//if(static_cast<int>(height) != ::TTF_FontHeight(myFont))
	//{
	//	//std::cout << "Changing font" << std::endl;
	//	TTF_CloseFont(myFont);
	//	if(myFontResource != NULL)
	//	{
	//		myFontResource = ::SDL_RWFromConstMem(myFontBuffer, myBufferLength);
	//		myFont = TTF_OpenFontRW(myFontResource, 1, height);
	//		if(myFont == NULL)
	//		{
	//			std::string s = "Cannot load font from resource";
	//			s += ::TTF_GetError();
	//			throw GuiException(s);
	//		}
	//	}
	//}

	int w = 0;
	int h = 0;
	::TTF_SizeText(myFont, text.c_str(), &w, &h);

	return (float)w;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
float SDLFont::getTextHeight(const std::string& text, unsigned int charHeight)
{
	int w = 0;
	int h = 0;
	::TTF_SizeText(myFont, text.c_str(), &w, &h);

	return (float)h;
}

} //end namespace