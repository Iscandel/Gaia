#include "libAppli.h"

#include "Gaia/Gaia.h"
#include "Gaia/SDLRenderer/SDLRenderer.h"

//SDL
void LibAppli::init(int winX, int winY, const std::string& winName)
{
	gaia::GuiManager* Manager = gaia::GuiManager::getInstance();

	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
	::SDL_EnableUNICODE(1);

    myScreen = SDL_SetVideoMode(winX, winY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(winName.c_str(), NULL);

	Manager->setWindowSize(winX, winY);
	gaia::SDLGraphics* gfx = new gaia::SDLGraphics(myScreen);
	//gfx->smoothImages(false);
	//gfx->optimizeDrawing(false);

	Manager->setGraphics(gfx);
}


void LibAppli::mainLoop()
{
	bool loop = true;

	TTF_Font* font = TTF_OpenFont("arial.ttf", 30);

	unsigned int currentTime = 0;
	unsigned int lastTime = 0;

	gaia::GuiManager* Manager = gaia::GuiManager::getInstance();
	
	while (loop)
    {
		lastTime = currentTime;
		currentTime = SDL_GetTicks();
		unsigned int elapsedTime = currentTime - lastTime;

		SDL_Event event;
        while(SDL_PollEvent(&event))
		{
			Manager->processEvent(gaia::SDLInput(event));
			if(event.type == SDL_QUIT)
			{
				loop = false;
			}
			//else if(event.type == ::SDL_KEYDOWN)
			//{
			//	std::cout << event.key.keysym.unicode << std::endl;
			//}
		}

		SDL_FillRect(myScreen, NULL, SDL_MapRGB(myScreen->format, 131, 214, 245));

		Manager->update(elapsedTime);
		Manager->draw();
		
		SDL_Color whiteColor = {255,255,255};
		SDL_Rect position;
		position.x = 0;
		position.y = 0;	

		std::string fps = gaia::tools::numToString(1000. / elapsedTime);
		::SDL_Surface* text = ::TTF_RenderText_Blended(font, fps.c_str(), whiteColor);
		SDL_BlitSurface(text, NULL, myScreen, &position); 
		::SDL_FreeSurface(text);
		SDL_Flip(myScreen);
	}

	::TTF_CloseFont(font);
}

void LibAppli::release()
{
	::SDL_FreeSurface(myScreen);
}