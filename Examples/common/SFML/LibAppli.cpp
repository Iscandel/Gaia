#include "libAppli.h"
#include "Gaia/Gaia.h"
#include "Gaia/SFMLRenderer/SFMLRenderer.h"
//#include "XMLGaia.h"
#include <SFML/Graphics.hpp>

//SFML
void LibAppli::init(int winX, int winY, const std::string& winName)
{
	gaia::GuiManager* Manager = gaia::GuiManager::getInstance();

	//const int FEN_X = 640;
	//const int FEN_Y = 480;

	myWindow = new sf::RenderWindow(sf::VideoMode(winX, winY), winName);
	//Fenetre.EnableKeyRepeat(false);

	Manager->setWindowSize(winX, winY);
	gaia::SFMLGraphics* gfx = new gaia::SFMLGraphics(myWindow);
	//gfx->smoothImages(false);
	//gfx->optimizeDrawing(false);

	Manager->setGraphics(gfx);
}


void LibAppli::mainLoop()
{
	int elapsed = myClock.getElapsedTime().asMilliseconds();
	//std::cout << 1000. / getElapsedTime() << std::endl;
	myClock.restart();

	gaia::GuiManager* Manager = gaia::GuiManager::getInstance();

	while(myWindow->isOpen())
	{
		sf::Event ev;
		while(myWindow->pollEvent(ev))
		{
			Manager->processEvent(gaia::SFMLInput(ev));

			if(ev.type == sf::Event::Closed)
			{
				myWindow->close();
			}
			else if(ev.type == sf::Event::KeyPressed)
			{
				std::cout << ev.key.code << std::endl;
			}
		}

		myWindow->clear(sf::Color(100, 100, 100));
		Manager->update(elapsed);
		Manager->draw();

		sf::Text fps;
		fps.setString(gaia::tools::numToString(1.f / elapsed * 1000));
		fps.setColor(sf::Color::White);
		myWindow->draw(fps);

		//std::cout << monA.val << std::endl;

		myWindow->display();
	}
}

void LibAppli::release()
{
	delete myWindow;
}