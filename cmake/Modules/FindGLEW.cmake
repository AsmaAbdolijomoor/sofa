# Find the GLEW headers and libraries
# Behavior is to first look for config files, such as the one installed by some package
# managers who provides their own cmake files. If no config files
# were found, this tries to find the library by looking at headers / lib file.
#
# Defines:
#   GLEW_FOUND : True if GLEW is found
#
# Provides target GLEW::GLEW.
find_package(GLEW QUIET)

if(TARGET GLEW::GLEW)
  set(GLEW_FOUND TRUE) # only GLEW_FOUND has been set
else()

  if(NOT GLEW_INCLUDE_DIR)
    find_path(GLEW_INCLUDE_DIR
      NAMES GL/glew.h
      PATH_SUFFIXES include
    )
  endif()

  if(NOT GLEW_LIBRARY)
    find_library(GLEW_LIBRARY
      NAMES GLEW glew32
      PATH_SUFFIXES lib
    )
  endif()

  if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
    set(GLEW_FOUND TRUE)
  else()
    if(GLEW_FIND_REQUIRED)
      message(FATAL_ERROR "Cannot find GLEW")
    endif()
  endif()

  if(GLEW_FOUND)
    set(GLEW_LIBRARIES ${GLEW_LIBRARY})
    set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})

    if(NOT TARGET GLEW::GLEW)
      add_library(GLEW::GLEW SHARED IMPORTED)
      set_property(TARGET GLEW::GLEW PROPERTY IMPORTED_LOCATION "${GLEW_LIBRARIES}")
      if(WIN32)
        set_property(TARGET GLEW::GLEW PROPERTY IMPORTED_IMPLIB "${GLEW_LIBRARIES}")
      endif()
      set_property(TARGET GLEW::GLEW PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}")
    endif()
  else()
  endif()
  mark_as_advanced(GLEW_INCLUDE_DIR GLEW_LIBRARY)
endif()
