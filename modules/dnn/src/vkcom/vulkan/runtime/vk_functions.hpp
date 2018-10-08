// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2017, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.

#ifndef OPENCV_DNN_VKCOM_VULKAN_RUNTIME_VK_FUNCTONS_HPP
#define OPENCV_DNN_VKCOM_VULKAN_RUNTIME_VK_FUNCTONS_HPP

#include "../../../precomp.hpp"
#include "../vulkan.h"

#define VK_ENTRY(func) extern PFN_##func func;
#define VK_GLOBAL_LEVEL_FUNC(func) extern PFN_##func func;
#define VK_GLOBAL_LEVEL_FUNC_MANDATORY(func) extern PFN_##func func;
#define VK_FUNC(func) extern PFN_##func func;
#define VK_FUNC_MANDATORY(func) extern PFN_##func func;

#include "function_list.inl"

#endif // OPENCV_DNN_VKCOM_VULKAN_RUNTIME_VK_FUNCTONS_HPP


