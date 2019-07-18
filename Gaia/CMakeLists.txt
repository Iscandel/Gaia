#GUIEnglish

file(
		GLOB_RECURSE
		source_files
		${CMAKE_CURRENT_SOURCE_DIR}/src/*
		${CMAKE_CURRENT_SOURCE_DIR}/include/*
)

add_library(Gaia ${source_files}) #SHARED OR STATIC is automatically determined


if(NOT BUILD_SHARED_LIBS)
	add_definitions(-DGAIA_STATIC)
else()
	add_definitions(-DGAIA_EXPORT)
endif()

if(BUILD_SHARED_LIBS)
	set_target_properties(Gaia PROPERTIES DEBUG_POSTFIX -d)
else()
	set_target_properties(Gaia PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(Gaia PROPERTIES RELEASE_POSTFIX -s)
endif()	