cmake_minimum_required(VERSION 3.22)
project(Sofa
    HOMEPAGE_URL https://www.sofa-framework.org/
) # Cannot use VERSION with patch like "00"

# Include custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include(SofaMacros)  # This should contain the definition of sofa_add_subdirectory

include(CMakeDependentOption)

# Manually define VERSION
set(Sofa_VERSION_MAJOR 24)
set(Sofa_VERSION_MINOR 06)
set(Sofa_VERSION_PATCH 99)
set(Sofa_VERSION ${Sofa_VERSION_MAJOR}.${Sofa_VERSION_MINOR}.${Sofa_VERSION_PATCH})

set(SOFA_URL "${CMAKE_PROJECT_HOMEPAGE_URL}")

set(SOFA_VERSION_STR "\"${Sofa_VERSION}\"")
set(SOFA_VERSION "${Sofa_VERSION_MAJOR}${Sofa_VERSION_MINOR}${Sofa_VERSION_PATCH}")

## Default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to Release as none was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Output Directories definition
set(ARCHIVE_OUTPUT_DIRECTORY lib)
set(RUNTIME_OUTPUT_DIRECTORY bin)
if(WIN32)
    set(LIBRARY_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
else()
    set(LIBRARY_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY})
endif()
## Set the output directories globally
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIRECTORY})

# Option for packaging
option(SOFA_BUILD_RELEASE_PACKAGE "Run package specific configure" OFF)

# Option to allow some dependencies such as cxxopts to be fetched by cmake if
# the package is not found
option(SOFA_ALLOW_FETCH_DEPENDENCIES "Allow compatible dependencies to be fetched if the package is not found by cmake.
  List of dependencies that can be fetched: cxxopts, gtest, metis, CImg" ON)

# Option to accelerate the compilation
# see https://cmake.org/cmake/help/v3.16/command/target_precompile_headers.html
# and https://cmake.org/cmake/help/v3.16/prop_tgt/DISABLE_PRECOMPILE_HEADERS.html

# https://cmake.org/cmake/help/latest/policy/CMP0127.html
if (${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.22)
    cmake_policy(SET CMP0127 NEW)
endif()
cmake_dependent_option(SOFA_BUILD_WITH_PCH_ENABLED 
    "Compile SOFA using precompiled header (to accelerate the build process)" OFF
    "CMAKE_VERSION VERSION_GREATER_EQUAL 3.16" OFF)
if(SOFA_BUILD_WITH_PCH_ENABLED)
    message("-- Precompiled headers: enabled (SOFA_BUILD_WITH_PCH_ENABLED is ON).")
else()
    message("-- Precompiled headers: disabled (SOFA_BUILD_WITH_PCH_ENABLED is OFF or CMake < 3.16).")
    set(DISABLE_PRECOMPILE_HEADERS ON)
endif()

## Change default install component and prefix
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME applications)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()
if(APPLE AND SOFA_BUILD_APP_BUNDLE)
    set(SOFA_BUILD_RELEASE_PACKAGE ON)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/runSofa.app/Contents/MacOS)
    message("SOFA_BUILD_APP_BUNDLE = ${SOFA_BUILD_APP_BUNDLE}\n"
        "  Forcing SOFA_BUILD_RELEASE_PACKAGE = ${SOFA_BUILD_RELEASE_PACKAGE}\n"
        "  Forcing CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}"
        )
endif()
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

# Remove generated CMake files, this prevents CMake from finding packages that
# were disabled (like, unchecked in cmake-gui) after being built once.
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/cmake)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/lib/cmake)
# Remove generated SofaPython configuration files, to prevent SofaPython from
# adding paths to disabled plugins.
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/etc/sofa/python.d)

## Custom Environment
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Sofa/framework/Config/cmake")
list(APPEND CMAKE_IGNORE_PATH "${CMAKE_INSTALL_PREFIX}") # ignore install directory for findXXX commands
include(SofaMacros)

install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/FindEigen3.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/macdeployqt.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/windeployqt.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/FindTinyXML2.cmake"
    DESTINATION lib/cmake/Modules
    COMPONENT headers
    )

## RPATH
if(UNIX)
    # RPATH is a field in ELF binaries that is used as a hint by the system
    # loader to find needed shared libraries.
    #
    # In the build directory, cmake creates binaries with absolute paths in
    # RPATH.  And by default, it strips RPATH from installed binaries.  Here we
    # use CMAKE_INSTALL_RPATH to set a relative RPATH.  By doing so, we avoid
    # the need to play with LD_LIBRARY_PATH to get applications to run.

    # see https://cmake.org/Wiki/CMake_RPATH_handling for $ORIGIN doc
    set(CMAKE_INSTALL_RPATH
        "$ORIGIN/../lib"
        "$$ORIGIN/../lib"
        )

    if(APPLE)
        set(CMAKE_MACOSX_RPATH ON)
        list(APPEND CMAKE_INSTALL_RPATH
            "@loader_path/../lib"
            "@executable_path/../lib"
            "@loader_path/../../Frameworks"
            "@executable_path/../../Frameworks"
            )
        set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    endif()
endif(UNIX)

### Windows config
if(MSVC)
    # WinDepPack
    set(SOFA_DEPENDENCY_PACK_DIR "${CMAKE_SOURCE_DIR}" CACHE PATH "Directory containing Windows Dependency Pack")
    if(NOT EXISTS ${SOFA_DEPENDENCY_PACK_DIR})
        # force back to default value
        set(SOFA_DEPENDENCY_PACK_DIR "${CMAKE_SOURCE_DIR}" CACHE PATH "Directory containing Windows Dependency Pack" FORCE)
    endif()
    list(APPEND CMAKE_INCLUDE_PATH ${SOFA_DEPENDENCY_PACK_DIR}/include)
    if(CMAKE_CL_64)
        list(APPEND CMAKE_LIBRARY_PATH ${SOFA_DEPENDENCY_PACK_DIR}/lib/win64)
    else()
        list(APPEND CMAKE_LIBRARY_PATH ${SOFA_DEPENDENCY_PACK_DIR}/lib/win32)
    endif()
    install(DIRECTORY ${SOFA_DEPENDENCY_PACK_DIR}/include/ DESTINATION include/extlibs/WinDepPack COMPONENT headers)
    install(DIRECTORY ${SOFA_DEPENDENCY_PACK_DIR}/licenses/ DESTINATION licenses COMPONENT applications)
endif()

### Testing
option(SOFA_BUILD_TESTS "Compile the automatic tests for Sofa, along with the gtest library." ON)

## Active or not the use of ccache
option(SOFA_USE_CCACHE "Compile using ccache optimization" OFF)
if(SOFA_USE_CCACHE)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        # Support Unix Makefiles and Ninja
        #TODO replace by <LANG>_COMPILER_LAUNCHER
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
    else()
        message(WARNING "ccache not found, disabling option")
        set(SOFA_USE_CCACHE OFF CACHE bool "Compile using ccache optimization" FORCE)
    endif()
endif()

### Ninja build pools
option(SOFA_NINJA_BUILD_POOLS "Activate the Ninja build pools feature, to limit the cores used by specific targets" OFF)

# Sofa.Config sets the environment (options, compiler flags, global variables)
sofa_add_subdirectory(library Sofa/framework/Config Sofa.Config ON)

### Extlibs
add_subdirectory(extlibs)

### Compatibility
option(SOFA_ENABLE_LEGACY_HEADERS "Enable the compatibility layer (headers located in legacy folders) and deprecated cmake modules." ON)
if(SOFA_ENABLE_LEGACY_HEADERS)
    message("Using legacy headers is enabled.")
endif()
sofa_add_subdirectory(library Sofa/framework/Compat Sofa.Compat ON WHEN_TO_SHOW "SOFA_ENABLE_LEGACY_HEADERS" VALUE_IF_HIDDEN OFF)

### SOFA (framework and components)
add_subdirectory(Sofa)

### Compatibility
# Deprecated (hollow) framework and component modules.
# All depend on SOFA_ENABLE_LEGACY_HEADERS
# Some still contain (maybe useful) components not moved in Sofa/ yet.
# TODO: finally empty those remnants
add_subdirectory(applications/collections/deprecated)

## Tutorials option
option(SOFA_BUILD_TUTORIALS "Build (most of) the tutorials available." OFF)

# SceneCreator plugin
# Library used by SOFA_BUILD_TESTS and SOFA_BUILD_TUTORIALS
sofa_add_subdirectory(plugin applications/plugins/SceneCreator SceneCreator OFF
    WHEN_TO_SHOW "NOT SOFA_BUILD_SCENECREATOR AND NOT SOFA_BUILD_TESTS AND NOT SOFA_BUILD_TUTORIALS AND NOT SOFA_BUILD_RELEASE_PACKAGE"
    VALUE_IF_HIDDEN "ON")

## Plugins
add_subdirectory(applications/plugins)

## Applications
add_subdirectory(applications/projects)

# Tutorial add subdirectory
if(SOFA_BUILD_TUTORIALS)
    add_subdirectory(applications/tutorials)
endif()

## SOFA scenes
option(SOFA_BUILD_ADD_SCENES "Add SOFA scenes as a project of the build." OFF)
if (SOFA_BUILD_ADD_SCENES)
    add_subdirectory(examples)
endif()

## SOFA shaders
option(SOFA_BUILD_ADD_SHADERS "Add SOFA shaders as a project of the build." OFF)
if (SOFA_BUILD_ADD_SHADERS)
    add_subdirectory(share/shaders)
endif()

## Build external projects at the same time
set(SOFA_EXTERNAL_DIRECTORIES "" CACHE STRING "list of paths separated by ';'")
if(NOT "${SOFA_EXTERNAL_DIRECTORIES}" STREQUAL "")
    foreach(dir ${SOFA_EXTERNAL_DIRECTORIES})
        get_filename_component(name ${dir} NAME) # Get the name of the actual directory
        message("Adding external directory: ${name} (${dir})")
        add_subdirectory(${dir} "${CMAKE_CURRENT_BINARY_DIR}/external_directories/${name}")
    endforeach()
endif()

## Custom
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/custom.cmake")
    message("Adding custom file")
    include( "custom.cmake" )
endif()

## IDE directories
# Sofa.Component
sofa_get_all_targets(all_targets)
foreach(target ${all_targets})
    if(target MATCHES "Sofa.Component.*" AND NOT target MATCHES ".*_relocatable_install")
        set_target_properties(${target} PROPERTIES FOLDER Sofa.Component) # IDE folder
    endif()
endforeach()
# Testing
if(TARGET Sofa.Testing) # No need to search for test targets if tests are not enabled
    sofa_get_all_targets(all_targets)
    foreach(target ${all_targets})
        if(target MATCHES ".*_test" OR target MATCHES ".*_simutest")
            set_target_properties(${target} PROPERTIES FOLDER Testing) # IDE folder
        endif()
    endforeach()
endif()
##

## Install configuration
#install(FILES "${CMAKE_BINARY_DIR}/CMakeCache.txt" DESTINATION . COMPONENT headers)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION . COMPONENT applications)
install(FILES "${CMAKE_SOURCE_DIR}/CHANGELOG.md" DESTINATION . COMPONENT applications)
install(FILES "${CMAKE_SOURCE_DIR}/LICENSE-LGPL.md" DESTINATION . COMPONENT applications)
install(FILES "${CMAKE_SOURCE_DIR}/Authors.txt" DESTINATION . COMPONENT applications)

option(SOFA_INSTALL_RESOURCES_FILES "Copy resources files (etc/, share/, examples/, tools/sofa-launcher/) when installing" ON)
## Install resource files
if(SOFA_INSTALL_RESOURCES_FILES)
    install(DIRECTORY share/ DESTINATION share/sofa COMPONENT resources)
    install(DIRECTORY examples/ DESTINATION share/sofa/examples COMPONENT resources)
    install(DIRECTORY tools/sofa-launcher/ DESTINATION share/sofa/sofa-launcher COMPONENT resources)
endif()

# Packaging
if(SOFA_BUILD_RELEASE_PACKAGE)
    include(SofaPackage)
endif()

## Export config
if(SOFA_USE_CONFIG_PACKAGE)
    export(TARGETS ${all_targets} NAMESPACE Sofa:: FILE SofaTargets.cmake)
    set(config_install_dir "lib/cmake/${PROJECT_NAME}")
    install(EXPORT SofaTargets
        FILE
            SofaTargets.cmake
        NAMESPACE
            Sofa::
        DESTINATION
            ${config_install_dir}
        COMPONENT
            config
    )
    include(CMakePackageConfigHelpers)
    configure_package_config_file(cmake/Config.cmake.in ${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${config_install_dir}
        PATH_VARS CMAKE_INSTALL_PREFIX
    )
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${config_install_dir}
        COMPONENT config
    )
    write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${Sofa_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
    )
endif()

# Configure files with cmake
configure_file("${CMAKE_SOURCE_DIR}/Sofa/framework/Config/config.h.in" "${CMAKE_BINARY_DIR}/include/Sofa/framework/Config/config.h" @ONLY)

# CPack configuration
include(SofaCPack)

# Experimental Python support
if(SOFA_BUILD_PYTHON AND NOT DEFINED SOFA_SKIP_PYTHON_SETUP)
    # install python/ if needed
    file(GLOB_RECURSE PYTHON_SCRIPTS python/*.py)
    if(NOT "${PYTHON_SCRIPTS}" STREQUAL "")
        install(FILES ${PYTHON_SCRIPTS} DESTINATION python COMPONENT applications)
    endif()

    # use "source" directory
    add_subdirectory("python")
endif()



