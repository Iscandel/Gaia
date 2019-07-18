# Find TinyXml
# The following variables are defined when the library was found :
#  TINYXML_FOUND - System has TinyXml
#  TINYXML_INCLUDE_DIRS - The TinyXml include directories
#  TINYXML_LIBRARIES - The libraries needed to use TinyXml
#
# If TinyXml is not installed in a standard path, use TINYXMLDIR to
# define it.
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_path(TINYXML_INCLUDE_DIR tinyxml/tinyxml.h
          PATH_SUFFIXES include
          PATHS
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/
          /usr/
          /sw # Fink
          /opt/local/ # DarwinPorts
          /opt/csw/ # Blastwave
          /opt/
          ${TINYXMLDIR}
          $ENV{TINYXMLDIR})
		  
set(FIND_TINYXML_LIB_PATHS ~/Library/Frameworks
							/Library/Frameworks
							/usr/local
							/usr
							/sw
							/opt/local
							/opt/csw
							/opt
							${TINYXMLDIR}
							$ENV{TINYXMLDIR})

# static debug library (STL version)
find_library(TINYXML_LIBRARY_DEBUG
                 NAMES tinyxmld_STL tinyxml-d tinyxml
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_TINYXML_LIB_PATHS})

# static release library (STL version)
find_library(TINYXML_LIBRARY_RELEASE
                 NAMES tinyxml_STL tinyxml
                 PATH_SUFFIXES lib64 lib
                 PATHS ${FIND_TINYXML_LIB_PATHS})

set(TINYXML_LIBRARIES ${TINYXML_LIBRARY_DEBUG} ${TINYXML_LIBRARY_RELEASE})
set(TINYXML_INCLUDE_DIRS ${TINYXML_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(tinyxml  DEFAULT_MSG
                                  TINYXML_LIBRARIES TINYXML_INCLUDE_DIRS)

if(TINYXML_FOUND)
	message(Found TinyXml : ${TINYXML_INCLUDE_DIRS})
else()
	message(FATAL_ERROR TinyXml not found.)
endif()
