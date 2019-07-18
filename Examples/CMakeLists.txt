cmake_minimum_required( VERSION 2.8 )

function( build_example NAME MAIN_CPP )

set(

	SOURCES
	MAIN_CPP
	${PROJECT_SOURCE_DIR}/Examples/Common/BaseAppli.cpp
	${PROJECT_SOURCE_DIR}/Examples/Common/BaseAppli.h
	)

	add_executable( ${NAME } ${SOURCES} )

	target_link_libraries( ${NAME} sfgui ${SFML_GRAPHICS_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_SYSTEM_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} )

	install(

		TARGETS ${NAME}

		RUNTIME DESTINATION ${SHARE_TARGET_DIR}/examples COMPONENT examples

	)

	install(

		FILES ${SOURCES}

		DESTINATION ${SHARE_TARGET_DIR}/examples COMPONENT examples

	)

endfunction()
