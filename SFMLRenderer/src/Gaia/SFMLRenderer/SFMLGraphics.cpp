///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "Gaia/SFMLRenderer/SFMLGraphics.h"
#include "Gaia/SFMLRenderer/SFMLTexture.h"
#include "Gaia/SFMLRenderer/SFMLImageLoader.h"
#include "Gaia/SFMLRenderer/SFMLFont.h"
#include "Gaia/SFMLRenderer/SFMLTools.h"
#include "Gaia/tools/Exceptions.h"

#if defined WIN32
	#include <windows.h>
#endif
#include <GL/gl.h>

namespace gaia
{
SFMLGraphics::SFMLGraphics(sf::RenderWindow* window)
:myRenderWindow(window)
{
	sf::Font* defaultFont = new sf::Font(/*sf::Font::getDefaultFont()*/);
	PtrFont pFont(new SFMLFont(defaultFont));
	setGlobalFont(pFont);

	BaseTexture::setLoader(new SFMLImageLoader);

	myWindow = myRenderWindow;

	//myOptimizeDrawing = true;
	//if(isOptimizedDrawing())
	//{
	//	myCacheImage.Create(640, 480);//myWindowSize.width, myWindowSize.height);
	//	myCacheImage.Clear(sf::Color(0,0,0,0));
	//	myWindow = &myCacheImage;
	//}
	//else
	//{
	//	myWindow = myRenderWindow;
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLGraphics::drawImage_impl(Image& image, int x, int y, int width, int height)
{
	PtrTexture im = image.getTexture();
	PtrSFMLTexture sfIm = boost::static_pointer_cast<SFMLTexture>(im); //static for perfs ?

	//PtrSFMLTexture sfIm = image.getTextureConvertie<SFMLTexture>();

	sf::Sprite sp;
	sp.setPosition(static_cast<float>(x), static_cast<float>(y));	
	sp.setTexture(sfIm->getSFMLImage()); //Or implicit conversion ?
	sp.setTextureRect(toSFMLRect<int>(image.getRect()));
	
	if(width == 0)  width = image.getRect().width; //right ? //width = im->getWidth();
	if(height == 0) height = image.getRect().height;; //right ? // height = im->getHeight();


	sp.setScale(static_cast<float>(width) / image.getRect().width, 
			  static_cast<float>(height) / image.getRect().height);
	myWindow->draw(sp);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLGraphics::drawLine_impl(const Point& c1, 
								 const Point& c2, 
								 const Color& col, 
								 float thickness)
{
	//sf::Color sfCol((sf::Uint8)col.r, (sf::Uint8)col.g, (sf::Uint8)col.b, (sf::Uint8)col.a);
	//sf::Shape line = sf::Shape::Line(static_cast<float>(c1.x), 
	//								  static_cast<float>(c1.y), 
	//								  static_cast<float>(c2.x), 
	//								  static_cast<float>(c2.y), 
	//								  thickness, 
	//								  sfCol);
	//myWindow->Draw(line);

	sf::Color sfCol = SFMLTools::fromGuiColor(col);
	sf::Vertex vertex;
	vertex.position = sf::Vector2f(static_cast<float>(c1.x),
		static_cast<float>(c1.y));
	vertex.color = sfCol;

	sf::Vertex vertex2;
	vertex2.position = sf::Vector2f(static_cast<float>(c2.x),
		static_cast<float>(c2.y));
	vertex2.color = sfCol;
	sf::VertexArray v; v.append(vertex); v.append(vertex2);
	v.setPrimitiveType(sf::Lines);

	myWindow->draw(v);

	//int width = 1, height = 1;
	//if(c1.x == c2.x)
	//{
	//	height = std::abs(c2.y - c1.y);
	//}
	//else
	//{
	//	width = std::abs(c2.x - c1.x);
	//}

	//sf::RectangleShape rect = sf::RectangleShape(
	//	sf::Vector2f(static_cast<float>(width),
	//	static_cast<float>(height))//,
	//);
	//rect.SetPosition(static_cast<float>(c1.x),	static_cast<float>(c1.y));
	//rect.SetFillColor(sfCol);

	//myWindow->Draw(rect);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLGraphics::drawRectangle_impl(const Point& topLeft, 
									  int width, 
									  int height, 
									  const Color& col, 
									  int outlineThickness,
									  const Color& outlineColor)
{
	sf::Color sfCol = SFMLTools::fromGuiColor(col);

	sf::RectangleShape rect = sf::RectangleShape(
		//static_cast<float>(topLeft.x),
		//static_cast<float>(topLeft.y),
		sf::Vector2f(static_cast<float>(width),
		static_cast<float>(height))//,
		//sfCol
	);
	rect.setPosition(static_cast<float>(topLeft.x),	static_cast<float>(topLeft.y));
	rect.setFillColor(sfCol);
	rect.setOutlineThickness(static_cast<float>(outlineThickness));
	rect.setOutlineColor(SFMLTools::fromGuiColor(outlineColor));

	myWindow->draw(rect);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLGraphics::pushClippingArea(const gaia::IntRect& rect)
{
	if(!myWindow)
		return;

	if(myWindowSize.height == 0)
	{
		throw GuiException("Window size not initialized");
	}
	//std::cout << "Window size not initialized" << std::endl;

	// Flush the window, to make sure that our OpenGL cube
	// will be rendered on top of the background sprite
	//myWindow->Flush();

	// Activate the window
	//myWindow->SetActive();

	// Clear the depth buffer
	//glClear(GL_DEPTH_BUFFER_BIT);

	glEnable (GL_SCISSOR_TEST);

	//Version gaia::Rect
	glScissor(rect.x,
		myWindowSize.height - (rect.y + rect.height),
		rect.width,
		rect.height);

	BaseGraphics::pushClippingArea(rect);

	//glDisable (GL_SCISSOR_TEST);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void SFMLGraphics::popClippingArea()
{
		if(!myWindow)
		return;

	// Flush the window, to make sure that our OpenGL cube
	// will be rendered on top of the background sprite
	//myWindow->Flush();

	// Activate the window
	//myWindow->SetActive();

	BaseGraphics::popClippingArea();

	glScissor(myCurrentSize.x,
		myWindowSize.height -(myCurrentSize.x + myCurrentSize.height),
		myCurrentSize.width,
		myCurrentSize.height);

	//glScissor(0,
	//	0,
	//	myWindowSize.GetSize().x,
	//	myWindowSize.GetSize().y);

	glDisable (GL_SCISSOR_TEST);
}

void SFMLGraphics::drawOptimized()
{
	//glEnable (GL_SCISSOR_TEST);

	//glScissor(0,0,1000,1000);
	//glDisable (GL_SCISSOR_TEST);

	myCacheImage.display();
	sf::Sprite sp(myCacheImage.getTexture());
	myRenderWindow->draw(sp);
}

void SFMLGraphics::onWindowSizeAssigned()
{
	myCacheImage.create(myWindowSize.width, myWindowSize.height);
	//myCacheImage.Clear(sf::Color(0,0,0,0));
}

void SFMLGraphics::optimizeDrawing(bool opti)
{
	BaseGraphics::optimizeDrawing(opti);

	if(isOptimizedDrawing())
	{
		myWindow = &myCacheImage;
		invalidate();
	}
	else
	{
		myWindow = myRenderWindow;
	}
}

void SFMLGraphics::beginDraw()
{
	//BaseGraphics::beginDraw();

	if(isInvalidated() && isOptimizedDrawing())
	{
		myCacheImage.clear(sf::Color(0,0,0,0));
	}
}

//void SFMLGraphics::endDraw()
//{
//}

void SFMLGraphics::smoothImages(bool smooth)
{
	BaseImageLoader& loader = BaseTexture::getLoader();

	SFMLImageLoader* sfmlLoader = dynamic_cast<SFMLImageLoader*>(&loader);
	if(sfmlLoader)
	{
		sfmlLoader->setSmooth(smooth);
	}
}

} //end namespace