///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SDLRenderer/SDLGraphics.h"
#include "Gaia/SDLRenderer/SDLTexture.h"
#include "Gaia/SDLRenderer/SDLImageLoader.h"
#include "Gaia/SDLRenderer/SDLFont.h"
#include "Gaia/SDLRenderer/SDLTools.h"
#include "Gaia/tools/Exceptions.h"

#include <SDL/SDL_rotozoom.h>

#include <cmath>

namespace gaia
{
SDLGraphics::SDLGraphics(SDL_Surface* screen)
:myScreen(screen)
,myWindow(NULL)
,myCacheSurface(NULL)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        myRmask = 0xff000000;
        myGmask = 0x00ff0000;
        myBmask = 0x0000ff00;
        myAmask = 0x000000ff;
#else
        myRmask = 0x000000ff;
        myGmask = 0x0000ff00;
        myBmask = 0x00ff0000;
        myAmask = 0xff000000; 	
#endif

	TTF_Font* defaultFont = NULL;

	static char defaultData[] = 
	{
		#include "Gaia/SDLRenderer/Arial.h"
	};

	//SDL_SetAlpha(myScreen, SDL_SRCALPHA, 0);

	const int DEFAULT_SIZE = 15;
	
	//SDL_RWops* resource =
	//	::SDL_RWFromConstMem(defaultData, sizeof(defaultData));
		//::SDL_RWFromConstMem(SDLFont::myDefaultData, sizeof(SDLFont::myDefaultData));

	//defaultFont = TTF_OpenFontRW(resource, 1, 15);
	//PtrFont pFont(new SDLFont(defaultFont));
	//PtrFont pFont(new SDLFont(resource, 15));
	PtrFont pFont(new SDLFont(defaultData,  sizeof(defaultData), DEFAULT_SIZE));
	setGlobalFont(pFont);

	BaseTexture::setLoader(new SDLImageLoader);

	myWindow = myScreen;
	//SDL_SetAlpha(myScreen, 0, SDL_ALPHA_OPAQUE); //Nouveau

	//myCacheSurface = ::SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, 640, 480, 32, 0,0,0,0);//myRmask, myGmask, myBmask, myAmask);
	//SDL_Surface* tmp = myCacheSurface;
	//myCacheSurface = ::SDL_DisplayFormatAlpha(myCacheSurface);

	//SDL_SetAlpha(myCacheSurface, 0, SDL_ALPHA_OPAQUE);
	//SDL_FillRect(myCacheSurface, NULL, ::SDL_MapRGBA(myCacheSurface->format, 0,0,0,0));
	//SDL_FreeSurface(tmp);
	//myOptimizeDrawing = true;
	//if(myOptimizeDrawing) myWindow = myCacheSurface;
}


//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLGraphics::drawImage_impl(Image& image, int x, int y, int width, int height)
{
	//PtrTexture im = image.getTexture();
	//PtrSDLTexture sdlIm = boost::static_pointer_cast<SDLTexture>(im); //static for perfs ?

	PtrSDLTexture sdlIm = image.getConvertedTexture<SDLTexture>();

	if(width == 0)  width = image.getRect().width;
	if(height == 0) height = image.getRect().height;

	//Compute the ratios between the image size and the required size
	double ratioX = (double)width / image.getRect().width;
	double ratioY = (double)height / image.getRect().height;

	//Position
	SDL_Rect destRect = toSDLRect(IntRect(x, y, 0, 0));

	//SDL image sub rect
	SDL_Rect subRect = toSDLRect(image.getRect());

	//Copy sub rectangle from source to a new surface
	SDL_Surface* tmp = &sdlIm->getSDLImage();
	int bpp = tmp->format->BytesPerPixel;

	Uint8* p = (Uint8*) tmp->pixels + image.getRect().y * tmp->pitch + image.getRect().x * bpp;

	SDL_Surface* trueSurface = ::SDL_CreateRGBSurfaceFrom(
		p, 
		image.getRect().width, 
		image.getRect().height, 
		32, 
		tmp->pitch, 
		tmp->format->Rmask, tmp->format->Gmask, tmp->format->Bmask, tmp->format->Amask
	);

	//SDL_Surface* trueSurface = ::SDL_CreateRGBSurface(
	//	SDL_HWSURFACE, 
	//	image.getRect().width, 
	//	image.getRect().height, 
	//	32, myRmask, myGmask, myBmask, myAmask
	//);

	//SDL_SetAlpha(&sdlIm->getSDLImage(), 0, SDL_ALPHA_OPAQUE);
	//
	//SDL_Rect resizedDest = {0, 0, 0, 0};
	//::SDL_BlitSurface(&sdlIm->getSDLImage(), &subRect, trueSurface, &resizedDest);

	//Let's resize our new surface according to the widget size
	SDL_Surface* surf = ::zoomSurface(trueSurface, ratioX, ratioY, SMOOTHING_ON);
	//SDL_SetAlpha(surf, 0, SDL_ALPHA_OPAQUE );

	//Finish by calling SDL's blit function
	::SDL_BlitSurface(surf, NULL, myWindow, &destRect);

	::SDL_FreeSurface(trueSurface);
	::SDL_FreeSurface(surf);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLGraphics::drawLine_impl(const Point& c1, 
								 const Point& c2, 
								 const Color& col, 
								 float /*thickness*/)
{
	double x = c2.x - c1.x;
	double y = c2.y - c1.y;
	double length = std::sqrt( x*x + y*y );

	double addx = x / length;
	double addy = y / length;

	x = c1.x;
	y = c1.y;

	::SDL_LockSurface(myWindow);
	for(double i = 0; i < length; i++)
	{
		setPixel(myWindow, (int)x, (int)y, SDL_MapRGBA(myWindow->format, col.r, col.g, col.b, col.a));
		x += addx;
		y += addy;
	}

	::SDL_UnlockSurface(myWindow);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLGraphics::drawRectangle_impl(const Point& topLeft, 
									  int width, 
									  int height, 
									  const Color& col,
									  int outlineThickness,
									  const Color& outlineColor)
{
	SDL_Rect rect = toSDLRect(IntRect(topLeft.x, topLeft.y, width, height));
	::SDL_FillRect(myWindow, &rect, SDL_MapRGBA(myWindow->format, col.r, col.g, col.b, col.a));

	if(outlineThickness > 0)
	{
		//Top rect
		SDL_Rect rect = toSDLRect(IntRect(topLeft.x, topLeft.y, width, outlineThickness));
		::SDL_FillRect(myWindow, &rect, SDL_MapRGBA(myWindow->format, col.r, col.g, col.b, col.a));
		//Left rect
		rect = toSDLRect(IntRect(topLeft.x, topLeft.y, outlineThickness, height));
		::SDL_FillRect(myWindow, &rect, SDL_MapRGBA(myWindow->format, col.r, col.g, col.b, col.a));
		//Bottom rect
		rect = toSDLRect(IntRect(topLeft.x, topLeft.y + height - outlineThickness , width, outlineThickness));
		::SDL_FillRect(myWindow, &rect, SDL_MapRGBA(myWindow->format, col.r, col.g, col.b, col.a));
		//Right rect
		rect = toSDLRect(IntRect(topLeft.x + width - outlineThickness, topLeft.y, outlineThickness, height));
		::SDL_FillRect(myWindow, &rect, SDL_MapRGBA(myWindow->format, col.r, col.g, col.b, col.a));
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLGraphics::pushClippingArea(const gaia::IntRect& rect)
{
	SDL_Rect sdlRect = toSDLRect(rect);;
	::SDL_SetClipRect(myWindow, &sdlRect);

	BaseGraphics::pushClippingArea(rect);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLGraphics::popClippingArea()
{
	BaseGraphics::popClippingArea();

	SDL_Rect sdlRect = toSDLRect(IntRect(myCurrentSize.x,
							myCurrentSize.y, 
							myCurrentSize.width, 
							myCurrentSize.height));
	::SDL_SetClipRect(myWindow, &sdlRect);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SDLGraphics::setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void SDLGraphics::drawOptimized() 
{
	SDL_Rect destRect = {0, 0};
	//SDL_SetAlpha(myWindow, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
	::SDL_BlitSurface(myWindow, NULL, myScreen, &destRect);
}

void SDLGraphics::onWindowSizeAssigned()
{
	::SDL_FreeSurface(myCacheSurface);

	myCacheSurface = ::SDL_CreateRGBSurface(
		SDL_HWSURFACE, 
		myWindowSize.width, 
		myWindowSize.height, 
		32,
		myRmask, myGmask, myBmask, myAmask);

	SDL_Surface* tmp = myCacheSurface;
	myCacheSurface = ::SDL_DisplayFormatAlpha(myCacheSurface);

	//SDL_SetAlpha(myCacheSurface, 0, SDL_ALPHA_OPAQUE); //nouveau
	//SDL_FillRect(myCacheSurface, NULL, ::SDL_MapRGBA(myCacheSurface->format, 0,0,0,0));
	SDL_FreeSurface(tmp);

	//int c = SDL_MapRGBA(myCacheSurface->format, 255, 0, 255, 0);
	//SDL_SetColorKey(myCacheSurface, SDL_SRCCOLORKEY, c);
}

void SDLGraphics::optimizeDrawing(bool opti)
{
	BaseGraphics::optimizeDrawing(opti);

	if(isOptimizedDrawing())
	{
		myWindow = myCacheSurface;
		invalidate();
	}
	else
	{
		myWindow = myScreen;
	}
}

void SDLGraphics::beginDraw()
{
	if(isInvalidated() && isOptimizedDrawing())
	{
		SDL_Rect dest;
		dest.x=0; dest.y = 0;
		
		SDL_FillRect(myCacheSurface, NULL, SDL_MapRGBA(myCacheSurface->format, 0, 0, 0, 0));
		//SDL_SetAlpha(myCacheSurface, 0, SDL_ALPHA_OPAQUE); //Nouveau
	}
}

   //// copy img on window
   // SDL_LockSurface(window);
   // SDL_LockSurface(img);    
   // memcpy(window->pixels, img->pixels, (img->w * img->h * img->format->BytesPerPixel));
   // SDL_UnlockSurface(window);
   // SDL_UnlockSurface(img);    

} //end namespace