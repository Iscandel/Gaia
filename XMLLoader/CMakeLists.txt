#XML loader

set(SFMLDIR "" CACHE PATH "Fill in the SFML root path if SFML was not found. You also have to fill in SFML_INCLUDE_DIR if headers are in a separate folder.")

file(
		GLOB_RECURSE
		source_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(XMLGaia ${source_files}) #SHARED OR STATIC is automatically determined
add_dependencies(XMLGaia Gaia)
link_directories("${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(
	 		XMLGaia 
	 		Gaia
)

include_directories("${PROJECT_SOURCE_DIR}/XMLLoader/include")

if(BUILD_SHARED_LIBS)
	set_target_properties(XMLGaia PROPERTIES DEBUG_POSTFIX -d)
	add_definitions(
					-DGAIA_XML_EXPORT
					-DTIXML_USE_STL
	)
else()
	set_target_properties(XMLGaia PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(XMLGaia PROPERTIES RELEASE_POSTFIX -s)
	add_definitions(
					-DSFML_STATIC
					-DGAIA_XML_STATIC
					-DGAIA_STATIC
					-TIXML_USE_STL
	)
endif()	

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/Dependencies/Headers")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/Dependencies/lib/msvc")
       
#find_package(TinyXml REQUIRED)
#
#if(TINYXML_FOUND)
#	if(CMAKE_BUILD_TYPE MATCHES "Debug")
#		set(XML_GAIA_LIBS ${TINYXML_LIBRARY_DEBUG})
#	else()
#		set(XML_GAIA_LIBS ${TINYXML_LIBRARY_RELEASE})
#	endif()
#
#	#include_directories("${TINYXML_INCLUDE_DIRS}")
#		
#	target_link_libraries(
#	 		XMLGaia 
#	 		${XML_GAIA_LIBS}
#	)
#endif()