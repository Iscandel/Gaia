#ifndef H__BASEAPPLI__H_04_01_2013_0215
#define H__BASEAPPLI__H_04_01_2013_0215

#include <string>

#define GAIA_SDL_APPLI
#ifdef GAIA_SDL_APPLI
	#include "./SDL/libAppli.h"
#else
	#include "./SFML/libAppli.h"
#endif

class BaseAppli
{
public:
	BaseAppli(int winX = 640, int winY = 480, const std::string& winName = "");

	void run();

	virtual void appliCreation() = 0;;

	void libInit();

	void libMainLoop();

	void libRelease();

protected:
	LibAppli* myLib;

	std::string myWindowName;
	int myWindowX;
	int myWindowY;
};

#endif