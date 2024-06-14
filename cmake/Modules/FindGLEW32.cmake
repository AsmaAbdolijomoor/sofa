# FindGLEW.cmake
# Locate the GLEW library
#
# This module defines the following variables:
#  GLEW_FOUND - True if GLEW was found
#  GLEW_INCLUDE_DIRS - GLEW include directories
#  GLEW_LIBRARIES - Libraries needed to link against GLEW

find_path(GLEW_INCLUDE_DIR GL/glew.h
    PATHS
    ${GLEW_ROOT_DIR}/include
    /usr/include
    /usr/local/include
    /opt/local/include
    /sw/include
    /Library/Frameworks/GLEW.framework/Headers
)

find_library(GLEW_LIBRARY_RELEASE NAMES glew32 glew glew32s
    PATHS
    ${GLEW_ROOT_DIR}/lib
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    /sw/lib
    /Library/Frameworks/GLEW.framework
)

find_library(GLEW_LIBRARY_DEBUG NAMES glew32d glewd
    PATHS
    ${GLEW_ROOT_DIR}/lib
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    /sw/lib
    /Library/Frameworks/GLEW.framework
)

if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY_RELEASE)
    set(GLEW_FOUND TRUE)
    set(GLEW_LIBRARIES_RELEASE ${GLEW_LIBRARY_RELEASE})
    set(GLEW_LIBRARIES_DEBUG ${GLEW_LIBRARY_DEBUG})
    set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
else()
    set(GLEW_FOUND FALSE)
endif()

mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY_RELEASE GLEW_LIBRARY_DEBUG)
