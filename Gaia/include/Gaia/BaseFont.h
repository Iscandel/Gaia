#ifndef H__FONT_130620111514__H
#define H__FONT_130620111514__H

///////////////////////////////////////////////////////////////////////////////
// Headers-GUI
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/Config.h"
#include "Gaia/Color.h"

///////////////////////////////////////////////////////////////////////////////
// Headers-STL
///////////////////////////////////////////////////////////////////////////////
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Headers-External
///////////////////////////////////////////////////////////////////////////////
#include <boost/smart_ptr.hpp>

namespace gaia
{
class BaseGraphics;

class BaseFont;

typedef boost::shared_ptr<BaseFont> PtrFont;

///////////////////////////////////////////////////////////////////////////////
/// \brief Base class aiming at handling a font.
///////////////////////////////////////////////////////////////////////////////
class GAIA_DLL BaseFont : public boost::enable_shared_from_this<BaseFont>
{
public:
	///////////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor.
	///////////////////////////////////////////////////////////////////////////////
	BaseFont(void);

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Default constructor.
	///////////////////////////////////////////////////////////////////////////////
	~BaseFont(void);

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
	virtual void drawText(BaseGraphics* gfx, 
						  const std::string& text, 
						  int x, 
						  int y, 
						  const Color& col, 
						  unsigned int charHeight) = 0;

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Computes the width of a given string, with a given character heigth.
	///
	/// \param text : Text for which we need the width.
	/// \param charHeight : Height of the character.
	///
	/// \return The text width.
	///////////////////////////////////////////////////////////////////////////////
	virtual float getTextWidth(const std::string& text, unsigned int charheight) = 0;

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Computes the height of a given string, with a given character heigth.
	///
	/// \param text : Text for which we need the width.
	/// \param charHeight : Height of the character.
	///
	/// \return The text width.
	///////////////////////////////////////////////////////////////////////////////
	virtual float getTextHeight(const std::string& text, unsigned int charHeight) = 0;

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Returns the global default font.
	///
	/// \return A smart pointer to the default font.
	///////////////////////////////////////////////////////////////////////////////
	static PtrFont getDefaultFont() {return myDefaultFont;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief Assigns the default font.
	///
	/// \param A smart pointer to the new default font.
	///////////////////////////////////////////////////////////////////////////////
	static void setDefaultFont(PtrFont font) {myDefaultFont = font;}

	///////////////////////////////////////////////////////////////////////////////
	/// \brief  returns and converts the font to a font class specified by
	/// the template parameter.
	///
	/// \param A smart pointer to the new default font.
	///////////////////////////////////////////////////////////////////////////////
	template<class T>
	boost::shared_ptr<T> getInherited() {return boost::static_pointer_cast<T>(shared_from_this());}

protected:
	/// A global default font that could be used for widget with text, and having non initialized font.
	static PtrFont myDefaultFont; 
};

} //end namespace

#endif