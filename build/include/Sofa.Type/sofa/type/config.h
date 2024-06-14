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

#define SOFATYPE_VERSION 24.06.99

#ifdef SOFA_BUILD_SOFA_TYPE
#  define SOFA_TARGET Sofa.Type
#  define SOFA_TYPE_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#  define SOFA_TYPE_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif


#ifdef SOFA_BUILD_SOFA_TYPE
#define SOFA_ATTRIBUTE_DISABLED__RGBACOLOR_AS_FIXEDARRAY()
#else
#define SOFA_ATTRIBUTE_DISABLED__RGBACOLOR_AS_FIXEDARRAY() \
    SOFA_ATTRIBUTE_DISABLED( \
        "v23.12", "v24.06", \
        "RGBAColor does not inherit anymore from sofa::type::fixed_array. Use respective functions accordingly.")
#endif
