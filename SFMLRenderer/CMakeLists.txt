#SFML Renderer
project(SFMLGaia)

if(NOT BUILD_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2.3 COMPONENTS graphics window system)
find_package(OpenGL REQUIRED)

file(
		GLOB_RECURSE
		inc_files
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

file(
		GLOB_RECURSE
		src_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

add_library(${PROJECT_NAME} ${src_files} ${inc_files}) #SHARED OR STATIC is automatically determined
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

install(
	TARGETS ${PROJECT_NAME}
	EXPORT Gaia-export
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
)

install(
	FILES
	${inc_files}
	DESTINATION "include/Gaia/SFMLRenderer"
)