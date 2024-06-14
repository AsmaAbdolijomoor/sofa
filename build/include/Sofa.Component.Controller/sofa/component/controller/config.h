/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#pragma once

#include <sofa/config.h>
#include <sofa/config/sharedlibrary_defines.h>

#ifdef SOFA_BUILD_SOFA_COMPONENT_CONTROLLER
#  define SOFA_TARGET Sofa.Component.Controller
#  define SOFA_COMPONENT_CONTROLLER_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#  define SOFA_COMPONENT_CONTROLLER_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

namespace sofa::component::controller
{
	constexpr const char* MODULE_NAME = "Sofa.Component.Controller";
	constexpr const char* MODULE_VERSION = "24.06.99";
} // namespace sofa::component::controller

#ifdef SOFA_BUILD_SOFA_COMPONENT_CONTROLLER
#define SOFA_ATTRIBUTE_DEPRECATED__RENAME_DATA_IN_CONTROLLER()
#else
#define SOFA_ATTRIBUTE_DEPRECATED__RENAME_DATA_IN_CONTROLLER() \
    SOFA_ATTRIBUTE_DEPRECATED( \
        "v24.06", "v24.12", \
        "Data renamed according to the guidelines")
#endif