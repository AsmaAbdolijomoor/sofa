# CMake package configuration file for SofaSimpleFem

if(NOT "${CMAKE_PROJECT_NAME}" STREQUAL "Sofa" OR NOT "${PROJECT_SOURCE_DIR}" MATCHES "${CMAKE_SOURCE_DIR}/.*")
    # The project doing find_package is not a subproject of SOFA or is not located inside SOFA
    get_property(SofaSimpleFem_SENT_DEPRECATION_MESSAGE GLOBAL PROPERTY PROPERTY_SofaSimpleFem_SENT_DEPRECATION_MESSAGE SET)
    if(NOT SofaSimpleFem_SENT_DEPRECATION_MESSAGE)
        message(WARNING "SofaSimpleFem module is deprecated. It will be removed at v23.06. Use Sofa.Component.Diffusion and Sofa.Component.SolidMechanics.FEM.Elastic instead.")
    endif()
    set_property(GLOBAL PROPERTY PROPERTY_SofaSimpleFem_SENT_DEPRECATION_MESSAGE TRUE)
endif()

### Expanded from @PACKAGE_GUARD@ by SofaMacrosInstall.cmake ###
include_guard()
list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../bin")
list(APPEND CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../lib")
################################################################

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was SofaSimpleFemConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

find_package(SofaBaseTopology QUIET REQUIRED)
find_package(SofaBaseLinearSolver QUIET REQUIRED)
find_package(Sofa.Component.Diffusion QUIET REQUIRED)
find_package(Sofa.Component.SolidMechanics.FEM.Elastic QUIET REQUIRED)

if(NOT TARGET SofaSimpleFem)
    include("${CMAKE_CURRENT_LIST_DIR}/SofaSimpleFemTargets.cmake")
endif()

check_required_components(SofaSimpleFem)
