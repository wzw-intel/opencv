// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2017, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.

#include "../../../precomp.hpp"
#include "../vulkan.h"
#include "vk_functions.hpp"

#if defined(_WIN32)
#include <windows.h>
typedef HMODULE VulkanHandle;
#define DEFAULT_VK_LIBRARY_PATH "vulkan-1.dll"
#define LOAD_VK_LIBRARY(path) LoadLibrary(path)
#define FREE_VK_LIBRARY(handle) FreeLibrary(handle)
#define GET_VK_ENTRY_POINT(handle) \
        (PFN_vkGetInstanceProcAddr)GetProcAddress(handle, "vkGetInstanceProcAddr");
#elif defined(__linux__)
#include <dlfcn.h>
#include <stdio.h>
typedef void* VulkanHandle;
#define DEFAULT_VK_LIBRARY_PATH "libvulkan.so"
#define LOAD_VK_LIBRARY(path) dlopen(path, RTLD_LAZY | RTLD_GLOBAL)
#define FREE_VK_LIBRARY(handle) dlclose(handle)
#define GET_VK_ENTRY_POINT(handle) \
        (PFN_vkGetInstanceProcAddr)dlsym(handle, "vkGetInstanceProcAddr");
#endif

namespace cv { namespace dnn { namespace vkcom {

static VulkanHandle handle = nullptr;
static bool loadVulkanFunctions()
{
#define VK_PFN(fun) \
    if(!(fun = (PFN_##fun)vkGetInstanceProcAddr(nullptr, #fun))) \
    { \
      fprintf(stderr, "Could not load Vulkan function: %s !", #fun); \
      return false; \
    }

#include "function_name_list.inl"

#undef VK_PFN
    return true;
}

bool loadVulkanRuntime()
{
    if (handle != nullptr)
        return handle;

    handle = LOAD_VK_LIBRARY(DEFAULT_VK_LIBRARY_PATH);
    if( handle == nullptr ) { 
        fprintf(stderr, "Could not load Vulkan library: %s!\n", DEFAULT_VK_LIBRARY_PATH);
        return false;
    }   

    vkGetInstanceProcAddr = GET_VK_ENTRY_POINT(handle);
    if (vkGetInstanceProcAddr)
    {
        if (loadVulkanFunctions())
            return true;
    }
    else
    {
        fprintf(stderr, "Could not load Vulkan entry function: vkGetInstanceProcAddr!\n");
        FREE_VK_LIBRARY();
        handle = nullptr;
        return false;
    }
}

}}} // namespace cv::dnn::vkcom
