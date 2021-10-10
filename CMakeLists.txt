CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Gaia)

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 9)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Set Debug / Release / MinSizeRel / RelWithDebInfo mode")
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Uncheck to build static libraries")
set(BUILD_XML TRUE CACHE BOOL "Check to build XML module")
set(BUILD_SFML_RENDERER TRUE CACHE BOOL "Check to build SFML renderer module")
set(BUILD_SDL_RENDERER TRUE CACHE BOOL "Check to build SFML renderer module")
set(BUILD_EXAMPLES TRUE CACHE BOOL "Check to build examples")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake/Modules/")


#if(NOT BUILD_SHARED_LIBS)
#	add_definitions(-DGAIA_STATIC)
#else()
#	add_definitions(-DGAIA_EXPORT)
#endif()

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

add_subdirectory(Gaia)

if(${BUILD_SFML_RENDERER})
	add_subdirectory(SFMLRenderer)
endif()

if(${BUILD_SDL_RENDERER})
	add_subdirectory(SDLRenderer)
endif()

if(${BUILD_XML})
	add_subdirectory(XMLLoader)
endif()

if(${BUILD_EXAMPLES})
	add_subdirectory(Examples)
endif()