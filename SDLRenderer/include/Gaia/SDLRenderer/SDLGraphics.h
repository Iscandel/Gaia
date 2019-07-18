#ifndef H__SFMLGRAPHICS__100620111958__H
#define H__SFMLGRAPHICS__100620111958__H

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLConfig.h"
#include "Gaia/BaseGraphics.h"

#include <SDL/SDL.h>

namespace gaia
{
///////////////////////////////////////////////////////////////////////////////
/// \brief SFML implementation of the graphics class.
///////////////////////////////////////////////////////////////////////////////
class GAIA_SDL_DLL SDLGraphics : public gaia::BaseGraphics
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///
	/// \param window : Pointer to the existing SDL main surface.
	///////////////////////////////////////////////////////////////////////////
	SDLGraphics(SDL_Surface* screen = NULL);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawImage method.
	///
	/// \param image : Image to draw.
	///
	/// \param x : X left top coordinate.
	///
	/// \param y : Y left top coordinate.
	///
	/// \param width : It can be different from image own width, this results in a
	/// resize.
	///
	/// \param width : It can be different from image own height, this results in a
	/// resize.
	///////////////////////////////////////////////////////////////////////////
	void drawImage_impl(Image& image, int x, int y, int width = 0, int height = 0);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawLine method.
	///
	/// \param c1 : Top left corner.
	/// \param c2 : Bottom right corner.
	/// \param col : Line color.
	/// \param thickness : Thickness of the line.
	///////////////////////////////////////////////////////////////////////////
	void drawLine_impl(const Point& c1, 
					   const Point& c2, 
					   const Color& col, 
					   float thickness = 1.f);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Implementation of the drawRectangle method
	///
	/// \param topLeft : Top left corner.
	/// \param width :Rectangle width.
	/// \param height : Rectangle height.
	/// \param col : Rectangle color.
	///////////////////////////////////////////////////////////////////////////
	void drawRectangle_impl(const Point& topLeft, 
							int width, 
							int height, 
							const Color& col,
							int outlineThickness,
							const Color& outlineColor);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Adds a new clipping area to the stack.
	///
	/// \param rect : clipping area.
	///////////////////////////////////////////////////////////////////////////
	void pushClippingArea(const gaia::IntRect& rect);

	//@override
	///////////////////////////////////////////////////////////////////////////
	/// \brief Removes the last clipping area (which is on top of the stack).
	///////////////////////////////////////////////////////////////////////////
	void popClippingArea();

	///////////////////////////////////////////////////////////////////////////
	/// \brief Returns the underlying SDL_Surface.
	///
	/// \return The SDL main surface.
	///////////////////////////////////////////////////////////////////////////
	SDL_Surface* getWindow() {return myWindow;}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Converts a GUI rect to a SDL rect.
	///
	/// \param rect : Gui rectangle to convert.
	///
	/// \return An equivalent SDL rectangle.
	///////////////////////////////////////////////////////////////////////////
	SDL_Rect toSDLRect(const IntRect& rect)
	{
		SDL_Rect res;

		res.x = static_cast<Sint16>(rect.x);
		res.y = static_cast<Sint16>(rect.y);
		
		res.w = static_cast<Uint16>(rect.width);
		res.h = static_cast<Uint16>(rect.height);

		return res;
	}

	///////////////////////////////////////////////////////////////////////////
	/// \brief Modifies the pixel of a surface at a given position.
	///
	/// \param surface : surface to modify.
	/// \param x : X position.
	/// \param y : Y position.
	/// \param pixel : Color to set.
	///////////////////////////////////////////////////////////////////////////
	void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

	//@override
	void drawOptimized();

	//@override
	void onWindowSizeAssigned();

	//@override
	void optimizeDrawing(bool opti);

	//@override
	void beginDraw();

	//void endDraw();
protected:
	const char* getDefaultData() const;

protected:
	SDL_Surface* myScreen;
	SDL_Surface* myWindow; //myTarget
	SDL_Surface* myCacheSurface;
	Uint32 myRmask;
    Uint32 myGmask;
    Uint32 myBmask;
    Uint32 myAmask;
};

} //end namespace

#endif