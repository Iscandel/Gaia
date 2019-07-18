#SFML Renderer

set(SFMLDIR "" CACHE PATH "Fill in the SFML root path if SFML was not found. You also have to fill in SFML_INCLUDE_DIR if headers are in a separate folder.")

file(
		GLOB_RECURSE
		source_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(SFMLGaia ${source_files}) #SHARED OR STATIC is automatically determined
add_dependencies(SFMLGaia Gaia)
link_directories("${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(
	 		SFMLGaia 
	 		Gaia
)

find_package(OpenGL REQUIRED)
target_link_libraries(
	 		SFMLGaia 
	 		${OPENGL_gl_LIBRARY}
)

include_directories("${PROJECT_SOURCE_DIR}/SFMLRenderer/include")

if(BUILD_SHARED_LIBS)
	set_target_properties(SFMLGaia PROPERTIES DEBUG_POSTFIX -d)
	add_definitions(
					-DGAIA_SFML_EXPORT
	)
else()
	set_target_properties(SFMLGaia PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(SFMLGaia PROPERTIES RELEASE_POSTFIX -s)
	add_definitions(
					-DSFML_STATIC
					-DGAIA_SFML_STATIC
					-DGAIA_STATIC
	)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()	

find_package(SFML 2.0 REQUIRED GRAPHICS WINDOW SYSTEM )

if(SFML_FOUND)
	if(CMAKE_BUILD_TYPE MATCHES "Debug")
		set(SFML_GAIA_LIBS ${SFML_SYSTEM_LIBRARY_DEBUG} 
					  ${SFML_WINDOW_LIBRARY_DEBUG} 
					  ${SFML_GRAPHICS_LIBRARY_DEBUG})
	else()
		set(SFML_GAIA_LIBS ${SFML_SYSTEM_LIBRARY_RELEASE} 
					  ${SFML_WINDOW_LIBRARY_RELEASE}
					  ${SFML_GRAPHICS_LIBRARY_RELEASE})
	endif()

	#include_directories("${SFML_INCLUDE_DIR}")
		
	target_link_libraries(
	 		SFMLGaia 
	 		${SFML_GAIA_LIBS}
	)
endif()