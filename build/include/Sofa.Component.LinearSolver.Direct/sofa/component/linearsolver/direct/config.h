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

#ifdef SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT
#  define SOFA_TARGET Sofa.Component.LinearSolver.Direct
#  define SOFA_COMPONENT_LINEARSOLVER_DIRECT_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#  define SOFA_COMPONENT_LINEARSOLVER_DIRECT_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

namespace sofa::component::linearsolver::direct
{
	constexpr const char* MODULE_NAME = "Sofa.Component.LinearSolver.Direct";
	constexpr const char* MODULE_VERSION = "24.06.99";
} // namespace sofa::component::linearsolver::direct

#ifdef SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT
#define SOFA_ATTRIBUTE_DISABLED__BTDLINEARSOLVER_DATABLOCKSIZE(msg)
#else
#define SOFA_ATTRIBUTE_DISABLED__BTDLINEARSOLVER_DATABLOCKSIZE(msg) \
    SOFA_ATTRIBUTE_DISABLED( \
        "v23.06", "v23.12", msg)
#endif // SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT

#ifdef SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT
#define SOFA_ATTRIBUTE_DISABLED__SOLVER_DIRECT_VERBOSEDATA()
#else
#define SOFA_ATTRIBUTE_DISABLED__SOLVER_DIRECT_VERBOSEDATA() \
    SOFA_ATTRIBUTE_DISABLED("v23.12", "v24.06", "This Data is no longer used")
#endif // SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT

#ifdef SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT
#define SOFA_ATTRIBUTE_DEPRECATED__SPARSECOMMON()
#else
#define SOFA_ATTRIBUTE_DEPRECATED__SPARSECOMMON() \
    SOFA_ATTRIBUTE_DEPRECATED("v24.06", "v24.12", "This function is no longer used")
#endif // SOFA_BUILD_SOFA_COMPONENT_LINEARSOLVER_DIRECT