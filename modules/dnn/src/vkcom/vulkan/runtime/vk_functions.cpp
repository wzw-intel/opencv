// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2017, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.

#include "../../../precomp.hpp"
#include "../vulkan.h"

#define VK_ENTRY(func) PFN_##func func = nullptr;
#define VK_GLOBAL_LEVEL_FUNC(func) PFN_##func func = nullptr;
#define VK_GLOBAL_LEVEL_FUNC_MANDATORY(func) PFN_##func func = nullptr;
#define VK_FUNC(func) PFN_##func func = nullptr;
#define VK_FUNC_MANDATORY(func) PFN_##func func = nullptr;

#include "function_list.inl"
