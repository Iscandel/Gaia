#include "Gaia/widgetRenderers/WindowImageRenderer.h"

namespace gaia
{
TitleBarImageRenderer::TitleBarImageRenderer(PtrWidget widget)
:TplWidgetRenderer(widget)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void TitleBarImageRenderer::draw_impl(BaseGraphics*)
{
	//Gfx->drawRectangle(Point(myWidget->getX(), myWidget->getY()), myWidget->getWidth(), myWidget->getHeight(), Color(0, 0, 250));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
WindowImageRenderer::WindowImageRenderer(PtrWidget widget)
:TplWidgetRenderer(widget)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void WindowImageRenderer::draw_impl(BaseGraphics* Gfx)
{
	bool parentClipping = false;
	BaseWidget* parent = myWidget->getParent();
	IWidgetRenderer* parentRenderer = NULL;

	if(parent)
	{
		parentRenderer = parent->getWidgetRenderer();
		if(parentRenderer)
		{
			parentClipping = parentRenderer->isClipping();
			parentRenderer->setClipping(false);
		}
	}

	const std::string leftEdge = "leftEdge";
	const std::string topLeftEdge = "topLeftEdge";
	const std::string topEdge = "topEdge";
	const std::string topRightEdge = "topRightEdge";
	const std::string rightEdge = "rightEdge";
	const std::string bottomLeftEdge = "bottomLeftEdge";
	const std::string bottomEdge = "bottomEdge";
	const std::string bottomRightEdge = "bottomRightEdge";
	const std::string center = "center";

	int leftWidth = 0;
	int topLeftWidth = 0;
	int topRightWidth = 0;
	//int topWidth = 0;
	int bottomHeight = 0;
	int topHeight = 0;
	int rightWidth = 0;
	int bottomLeftHeight = 0;
	int bottomLeftWidth = 0;
	int bottomRightWidth = 0;
	int	bottomRightHeight = 0;

	if(imageExists(topLeftEdge))
	{
		topLeftWidth = myImages[topLeftEdge].getRect().width;
		//topHeight = myImages[topLeftEdge].getRect().height;
		Gfx->drawImage(
			myImages[topLeftEdge], 
			0,//myWidget->getX(), 
			0,//myWidget->getY(), 
			0, 
			0);
	}
	if(imageExists(topRightEdge))
	{
		topRightWidth = myImages[topRightEdge].getRect().width;
		//topHeight = myImages[topLeftEdge].getRect().height;
		Gfx->drawImage(
			myImages[topRightEdge], 
			/*myWidget->getX() +*/ myWidget->getWidth() - topRightWidth, 
			0,//myWidget->getY(), 
			0, 
			0);
	}
	if(imageExists(topEdge))
	{
		//topWidth = myImages[topEdge].getRect().width;
		topHeight = myImages[topEdge].getRect().height;
		Gfx->drawImage(
			myImages[topEdge], 
			/*myWidget->getX() +*/ topLeftWidth, 
			0,//myWidget->getY(), 
			myWidget->getWidth() - topLeftWidth - topRightWidth, 
			0);
	}

	if(imageExists(leftEdge))
	{
		if(imageExists(bottomEdge))
		{
			bottomHeight = myImages[bottomEdge].getRect().height;
		}
		Gfx->drawImage(
			myImages[leftEdge], 
			0,//myWidget->getX(), 
			/*myWidget->getY() +*/ topHeight, 
			0, 
			myWidget->getHeight() - topHeight - bottomHeight);

		leftWidth = myImages[leftEdge].getRect().width;
	}

	if(imageExists(rightEdge))
	{
		if(imageExists(bottomEdge))
		{
			bottomHeight = myImages[bottomEdge].getRect().height;
		}
		rightWidth = myImages[rightEdge].getRect().width;
		Gfx->drawImage(
			myImages[rightEdge], 
			/*myWidget->getX() +*/ myWidget->getWidth() - rightWidth, 
			/*myWidget->getY() +*/ topHeight, 
			0, 
			myWidget->getHeight() - topHeight - bottomHeight);
	}
	if(imageExists(bottomLeftEdge))
	{
		bottomLeftHeight = myImages[bottomLeftEdge].getRect().height;
		bottomLeftWidth = myImages[bottomLeftEdge].getRect().width;

		Gfx->drawImage(
			myImages[bottomLeftEdge], 
			0,//myWidget->getX(), 
			/*myWidget->getY() +*/ myWidget->getHeight() - bottomHeight, 
			0, 
			bottomLeftHeight);
	}
	if(imageExists(bottomRightEdge))
	{
		bottomRightWidth = myImages[bottomRightEdge].getRect().width;
		bottomRightHeight = myImages[bottomRightEdge].getRect().height;
		Gfx->drawImage(
			myImages[bottomRightEdge], 
			/*myWidget->getX() +*/ myWidget->getWidth() - bottomRightWidth, 
			/*myWidget->getY() +*/ myWidget->getHeight() - bottomHeight, 
			0, 
			bottomRightHeight);
	}
	if(imageExists(bottomEdge))
	{
		bottomHeight = myImages[bottomEdge].getRect().height;
		Gfx->drawImage(
			myImages[bottomEdge], 
			/*myWidget->getX() +*/ bottomLeftWidth, 
			/*myWidget->getY() +*/ myWidget->getHeight() - bottomHeight,
			myWidget->getWidth() - bottomLeftWidth - bottomRightWidth , 
			bottomHeight);
	}
	if(imageExists(center))
	{
		Gfx->drawImage(
			myImages[center], 
			/*myWidget->getX() +*/ leftWidth, 
			/*myWidget->getY() +*/ topHeight, 
			myWidget->getWidth() - leftWidth - rightWidth, 
			myWidget->getHeight() - topHeight - bottomHeight);
	}

	if(parent)
	{
		if(parent->getWidgetRenderer())
		{
			parentRenderer->setClipping(parentClipping);
		}
	}
}

Window::PrivResizing::pos WindowImageRenderer::getEdge(int x, int y)
{	
	const std::string leftEdge = "leftEdge";
	const std::string topLeftEdge = "topLeftEdge";
	const std::string topEdge = "topEdge";
	const std::string topRightEdge = "topRightEdge";
	const std::string rightEdge = "rightEdge";
	const std::string bottomLeftEdge = "bottomLeftEdge";
	const std::string bottomEdge = "bottomEdge";
	const std::string bottomRightEdge = "bottomRightEdge";
	const std::string center = "center";

	int topHeight = myImages[topEdge].getRect().height;
	int bottomHeight = 0;
	if(imageExists(bottomEdge))
	{
		bottomHeight = myImages[bottomEdge].getRect().height;
	}

	if(imageExists(leftEdge))
	{
		IntRect rect = myImages[leftEdge].getRect();
		rect.x = 0; rect.y = topHeight;
		rect.height = myWidget->getHeight() - topHeight - bottomHeight;
		if(rect.contains(x, y))
			return Window::PrivResizing::LEFT;
	}

	if(imageExists(topLeftEdge))
	{
		IntRect rect = myImages[topLeftEdge].getRect();
		rect.x = 0; rect.y = 0;
		
		if(rect.contains(x, y))
			return Window::PrivResizing::TOP_LEFT;
	}
	
	if(imageExists(topEdge))
		if(myImages[topEdge].getRect().contains(x, y))
			return Window::PrivResizing::TOP;

	if(imageExists(topRightEdge))
		if(myImages[topRightEdge].getRect().contains(x, y))
			return Window::PrivResizing::TOP_RIGHT;

	if(imageExists(rightEdge))
		if(myImages[rightEdge].getRect().contains(x, y))
			return Window::PrivResizing::RIGHT;
	
	if(imageExists(bottomLeftEdge))
		if(myImages[bottomLeftEdge].getRect().contains(x, y))
			return Window::PrivResizing::BOTTOM_LEFT;

	if(imageExists(bottomEdge))
	{
		IntRect rect = myImages[bottomEdge].getRect();
		rect.x = 0; rect.y = myWidget->getHeight() - bottomHeight;
		rect.width = myWidget->getWidth(); //- ... - ...
		if(rect.contains(x, y))
			return Window::PrivResizing::BOTTOM;
	}

	if(imageExists(bottomRightEdge))
		if(myImages[bottomRightEdge].getRect().contains(x, y))
			return Window::PrivResizing::BOTTOM_RIGHT;
	
	return Window::PrivResizing::NONE;
}

} //end namespace