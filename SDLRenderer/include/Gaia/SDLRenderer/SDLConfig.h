#ifndef H__CONFIG_170920110138__H
#define H__CONFIG_170920110138__H

#ifdef _MSC_VER

	#pragma warning(disable : 4251)

#endif

#if (defined(WIN32) || defined(__WIN32__) || defined(_WIN32)) && !defined(GAIA_SDL_STATIC)
	#if defined(GAIA_SDL_EXPORT)

		#define GAIA_SDL_DLL __declspec(dllexport)

	#else

		#define GAIA_SDL_DLL __declspec(dllimport)
	
	#endif
#else

	#define GAIA_SDL_DLL

#endif

#endif //End guards