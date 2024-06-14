# FindTinyXML2.cmake
# Locate TinyXML2 library
#
# This module defines
#  TINYXML2_INCLUDE_DIR, where to find tinyxml2.h, etc.
#  TINYXML2_LIBRARIES, libraries to link against to use TinyXML2.
#  TINYXML2_FOUND, If false, do not try to use TinyXML2.

if (NOT TINYXML2_INCLUDE_DIR)
  find_path(TINYXML2_INCLUDE_DIR
    NAMES tinyxml2.h
    HINTS ${TINYXML2_ROOT} ${TINYXML2_INCLUDE_DIR} ${TINYXML2_ROOT}/include ${TINYXML2_ROOT}/tinyxml2-10.0.0
  )
endif()

if (NOT TINYXML2_LIBRARY)
  find_library(TINYXML2_LIBRARY
    NAMES tinyxml2
    HINTS ${TINYXML2_ROOT} ${TINYXML2_LIBRARY_DIR} ${TINYXML2_ROOT}/lib ${TINYXML2_ROOT}/tinyxml2-10.0.0
  )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TinyXML2 DEFAULT_MSG
  TINYXML2_INCLUDE_DIR TINYXML2_LIBRARY)

if (TINYXML2_FOUND)
  set(TINYXML2_LIBRARIES ${TINYXML2_LIBRARY})
else()
  set(TINYXML2_LIBRARIES)
endif()

mark_as_advanced(TINYXML2_INCLUDE_DIR TINYXML2_LIBRARY)


# If TinyXML2 is manually specified, create the target
if(TINYXML2_INCLUDE_DIR AND TINYXML2_LIBRARY)
  if(NOT TARGET tinyxml2::tinyxml2)
    add_library(tinyxml2::tinyxml2 STATIC IMPORTED)
    set_target_properties(tinyxml2::tinyxml2 PROPERTIES
      IMPORTED_LOCATION "${TINYXML2_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${TINYXML2_INCLUDE_DIR}"
    )
  endif()
endif()
