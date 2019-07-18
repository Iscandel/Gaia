#ifndef H__LIBAPPLI__H_04_01_2013_0226
#define H__LIBAPPLI__H_04_01_2013_0226
#include <SFML/Graphics.hpp>
//SFML

class sf::RenderWindow;

class LibAppli
{
public:
	void init(int winX, int winY, const std::string& winName);

	void mainLoop();

	void release();

protected:
	sf::RenderWindow* myWindow;
	sf::Clock myClock;
};

#endif