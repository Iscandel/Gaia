#include "BaseAppli.h"
#include "Gaia/Gaia.h"

#include <iostream>

BaseAppli::BaseAppli(int winX, int winY, const std::string& winName)
:myWindowName(winName)
,myWindowX(winX)
,myWindowY(winY)
{
	myLib = new LibAppli;
}

void BaseAppli::run()
{
		try
		{
			libInit();
			appliCreation();
			libMainLoop();
			libRelease();
		}
		catch(const gaia::GuiException& msg)
		{
			std::cout << msg.what() << std::endl;
			gaia::ILogger::log(gaia::ILogger::ERRORS) << msg.what() << "\n";
			getchar();
		}
		catch(const std::exception& msg)
		{
			std::cout << msg.what() << std::endl;
			gaia::ILogger::log(gaia::ILogger::ERRORS) << msg.what() << "\n";
			getchar();
		}
		catch(...)
		{
			std::cout << "what ??" << std::endl;
		
			getchar();
		}
}

	
	void BaseAppli::libInit()
	{
		myLib->init( myWindowX, myWindowY, myWindowName);
	}

	void BaseAppli::libMainLoop()
	{
		myLib->mainLoop();
	}

	void BaseAppli::libRelease()
	{
		myLib->release();
	}