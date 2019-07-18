#SDL Renderer


set(SDLDIR ${SDLDIR} CACHE PATH "Fill in the SDL root path if SDL was not found. You also have to fill in SDL_INCLUDE_DIR if headers are in a separate folder.")

file(
		GLOB_RECURSE
		source_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(SDLGaia ${source_files}) #SHARED OR STATIC is automatically determined
add_dependencies(SDLGaia Gaia)
link_directories("${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(
	 		SDLGaia 
	 		Gaia
)

include_directories("${PROJECT_SOURCE_DIR}/SDLRenderer/include")

if(BUILD_SHARED_LIBS)
	set_target_properties(SDLGaia PROPERTIES DEBUG_POSTFIX -d)
	add_definitions(
					-DGAIA_SDL_EXPORT
	)
else()
	set_target_properties(SDLGaia PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(SDLGaia PROPERTIES RELEASE_POSTFIX -s)
	add_definitions(
					-DSDL_STATIC
					-DGAIA_SDL_STATIC
					-DGAIA_STATIC
	)
endif()	

set(SDL_BUILDING_LIBRARY TRUE)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_gfx REQUIRED)

if(SDL_FOUND AND SDLIMAGE_FOUND AND SDLTTF_FOUND AND SDLGFX_FOUND)
	set(SDL_GAIA_LIBS ${SDL_LIBRARY} 
			${SDLIMAGE_LIBRARY} 
			${SDLTTF_LIBRARY}
			${SDLGFX_LIBRARY})

	#include_directories("${SDL_INCLUDE_DIR}")
	#include_directories("${SDLIMAGE_INCLUDE_DIR}")
	#include_directories("${SDLTTF_INCLUDE_DIR}")
	#include_directories("${SDLGFX_INCLUDE_DIR}")
		
	target_link_libraries(
	 		SDLGaia 
	 		${SDL_GAIA_LIBS}
	)
endif()