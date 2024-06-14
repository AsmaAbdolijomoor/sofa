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

#ifdef SOFA_BUILD_SOFA_COMPONENT_COLLISION_DETECTION_ALGORITHM
#  define SOFA_TARGET Sofa.Component.Collision.Detection.Algorithm
#  define SOFA_COMPONENT_COLLISION_DETECTION_ALGORITHM_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#  define SOFA_COMPONENT_COLLISION_DETECTION_ALGORITHM_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

#ifdef SOFA_BUILD_SOFA_COMPONENT_COLLISION_DETECTION_ALGORITHM
#define SOFA_ATTRIBUTE_DISABLED__RENAME_COLLISIONPIPELINE()
#else
#define SOFA_ATTRIBUTE_DISABLED__RENAME_COLLISIONPIPELINE() \
    SOFA_ATTRIBUTE_DISABLED( \
        "v23.06", "v23.12", \
        "DefaultPipeline renamed as CollisionPipeline in #3590: sofa/component/collision/detection/algorithm/CollisionPipeline.h")
#endif

#ifdef SOFA_BUILD_SOFA_COMPONENT_COLLISION_DETECTION
#  define SOFA_ATTRIBUTE_DISABLED__DRAWNARROWPHASE()
#else
# define SOFA_ATTRIBUTE_DISABLED__DRAWNARROWPHASE() \
    SOFA_ATTRIBUTE_DISABLED( \
        "v23.12", "v24.06", "This data is not used anymore: the drawing is now controlled by a draw flag")
#endif

#ifdef SOFA_BUILD_SOFA_COMPONENT_COLLISION_DETECTION_ALGORITHM
#define SOFA_ATTRIBUTE_DEPRECATED__RENAME_DATA_IN_COLLISION_DETECTION_ALGORITHM()
#else
#define SOFA_ATTRIBUTE_DEPRECATED__RENAME_DATA_IN_COLLISION_DETECTION_ALGORITHM() \
    SOFA_ATTRIBUTE_DEPRECATED(\
        "v24.06", "v24.12",\
        "data renamed according to the guidelines")
#endif

#ifdef SOFA_BUILD_SOFA_COMPONENT_COLLISION_DETECTION_ALGORITHM
#define SOFA_ATTRIBUTE_DEPRECATED__REMOVE_BDRAW_DATA()
#else
#define SOFA_ATTRIBUTE_DEPRECATED__REMOVE_BDRAW_DATA() \
    SOFA_ATTRIBUTE_DEPRECATED(\
        "v24.06", "v24.12",\
        "This Data was not used")
#endif

namespace sofa::component::collision::detection::algorithm
{
	constexpr const char* MODULE_NAME = "Sofa.Component.Collision.Detection.Algorithm";
	constexpr const char* MODULE_VERSION = "24.06.99";
} // namespace sofa::component::collision::geometry::algorithm
