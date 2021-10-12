#Lib gaia
project(LibGaia)
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

set(target_name gaia)
add_library(${target_name} ${inc_files} ${src_files})

target_include_directories(${target_name}
	PUBLIC 
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(NOT BUILD_SHARED_LIBS)
	add_definitions(-DGAIA_STATIC)
else()
	add_definitions(-DGAIA_EXPORT)
endif()

if(BUILD_SHARED_LIBS)
	set_target_properties(${target_name}  PROPERTIES DEBUG_POSTFIX -d)
else()
	set_target_properties(${target_name} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${target_name} PROPERTIES RELEASE_POSTFIX -s)
endif()	

install(
	TARGETS gaia
	EXPORT Gaia-export
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/Gaia
        DESTINATION "include"
        FILES_MATCHING PATTERN "*.h" 
)
