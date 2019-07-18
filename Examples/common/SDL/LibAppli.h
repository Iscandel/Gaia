#ifndef H__LIBAPPLI__H_30_08_2013_0133
#define H__LIBAPPLI__H_30_08_2013_0133

//SDL

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL_Image.h"

#include <string>

class LibAppli
{
public:
	void init(int winX, int winY, const std::string& winName);

	void mainLoop();

	void release();

protected:
	SDL_Surface* myScreen;
};

#endif