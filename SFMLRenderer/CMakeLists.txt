#SFML Renderer
project(SFMLGaia)

if(NOT BUILD_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2.3 COMPONENTS graphics window system)
find_package(OpenGL REQUIRED)

file(
		GLOB_RECURSE
		source_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(${PROJECT_NAME} ${source_files}) #SHARED OR STATIC is automatically determined
add_dependencies(${PROJECT_NAME} gaia)
#target_link_directories("${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(
	${PROJECT_NAME}
	PUBLIC gaia sfml-graphics ${OPENGL_gl_LIBRARY}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC 
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)


#find_package(OpenGL REQUIRED)
#target_link_libraries(
#	 		SFMLGaia 
#	 		${OPENGL_gl_LIBRARY}
#)

#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/SFMLRenderer/include")

if(BUILD_SHARED_LIBS)
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)
	add_definitions(
					-DGAIA_SFML_EXPORT
	)
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX -s)
	add_definitions(
					-DSFML_STATIC
					-DGAIA_SFML_STATIC
					-DGAIA_STATIC
	)
endif()	