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

#define VK_PFN(func) extern PFN_##func func;

#include "function_name_list.inl"

#undef VK_PFN

#endif // OPENCV_DNN_VKCOM_VULKAN_RUNTIME_VK_FUNCTONS_HPP


