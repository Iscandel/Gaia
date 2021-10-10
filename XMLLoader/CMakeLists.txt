#XML loader
project(XMLGaia)

set(tinyxml_dir ext/tinyxml)
set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/Gaia/XMLLoader)
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include/Gaia/XMLLoader)

file(
		GLOB_RECURSE
		source_files
		${tinyxml_dir}/tinystr.cpp
		${tinyxml_dir}/tinyxml.cpp
		${tinyxml_dir}/tinyxmlerror.cpp
		${tinyxml_dir}/tinyxmlparser.cpp
		${src_dir}/XMLGuiLoader.cpp
		${src_dir}/XMLWidgetLookLoader.cpp
		${include_dir}/XMLConfig.h
		${include_dir}/XMLGaia.h
		${include_dir}/XMLGuiLoader.h
		${include_dir}/XMLWidgetLookLoader.h
)

add_library(XMLGaia ${source_files}) #SHARED OR STATIC is automatically determined
add_dependencies(XMLGaia gaia)
#link_directories("${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(
	 		XMLGaia 
	 		gaia
)

target_include_directories(XMLGaia
	PUBLIC 
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(XMLGaia
	PRIVATE	
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ext>
)

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
					#-DSFML_STATIC
					-DGAIA_XML_STATIC
					#-DGAIA_STATIC
					-TIXML_USE_STL
	)
endif()	
