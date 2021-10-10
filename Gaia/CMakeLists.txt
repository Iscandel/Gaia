#Lib gaia
project(LibGaia)
file(
		GLOB_RECURSE
		source_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

set(target_name gaia)
add_library(${target_name} ${source_files})

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