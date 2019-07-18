///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SFMLRenderer/SFMLFont.h"
#include "Gaia/SFMLRenderer/SFMLGraphics.h"
#include "Gaia/tools/Exceptions.h"

namespace gaia
{
SFMLFont::SFMLFont(void)
:myFont(NULL)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SFMLFont::~SFMLFont(void)
{
	delete myFont;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SFMLFont::SFMLFont(const std::string& path)
{
	myFont = new sf::Font;

	if(!myFont->loadFromFile(path))
	{
		throw GuiException("Cannot load sf::Font from : " + path + " in SFMLFont.cpp");
	}

	myString.setFont(*myFont);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
SFMLFont::SFMLFont(sf::Font* font)//, const std::string& s)
{
	if(!font)
	{
		throw GuiException("Null pointer to sf::Font in SFMLFont.cpp");
	}

	myFont = font;
	myString.setFont(*myFont);
	//myString.SetFont(*font);
	//myString.SetString(s);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLFont::setFont(sf::Font* newFont)
{
	delete myFont;

	if(newFont)
		myFont = newFont;
	else
		throw GuiException("Null pointer to sf::Font in SFMLFont.cpp");

	myString.setFont(*myFont);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLFont::drawText(BaseGraphics* graphics, 
						const std::string& text, 
						int x, 
						int y, 
						const Color& col, 
						unsigned int characterHeight)
{
	myString.setString(text);
	myString.setPosition(static_cast<float>(x), static_cast<float>(y));
	sf::Color sfCol((sf::Uint8)col.r, 
					(sf::Uint8)col.g, 
					(sf::Uint8)col.b, 
					(sf::Uint8)col.a);

	myString.setColor(sfCol);
	myString.setCharacterSize(characterHeight);

	SFMLGraphics* sfGfx = static_cast<SFMLGraphics*>(graphics);
	//assert(sfGfx);
	
	sf::RenderTarget* win = sfGfx->getWindow();

	win->draw(myString);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
float SFMLFont::getTextWidth(const std::string& text, unsigned int charHeight)
{
	sf::Text tmp;
	tmp.setFont(*myFont);//myString.GetFont());
	tmp.setCharacterSize(charHeight);//myString.GetCharacterSize());
	tmp.setString(text);

	return tmp.getGlobalBounds().width;
}

float SFMLFont::getTextHeight(const std::string& text, unsigned int charHeight)
{
	sf::Text tmp;
	tmp.setFont(*myFont);//myString.GetFont());
	tmp.setCharacterSize(charHeight);//myString.GetCharacterSize());
	tmp.setString(text);

	return tmp.getGlobalBounds().height;
}

} //end namespace