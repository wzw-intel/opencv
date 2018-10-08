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

bool loadVulkanFunctions(VkInstance& instance)
{
#define VK_FUNC(fun) \
    fun = (PFN_##fun)vkGetInstanceProcAddr(instance, #fun);

#define VK_FUNC_MANDATORY(fun) \
    VK_FUNC(fun) \
    if(!fun) \
    { \
      fprintf(stderr, "Could not load Vulkan function: %s !\n", #fun); \
      return false; \
    }

#include "function_list.inl"

    return true;
}

bool loadVulkanGlobalFunctions()
{
#define VK_GLOBAL_LEVEL_FUNC(fun) \
    fun = (PFN_##fun)vkGetInstanceProcAddr(nullptr, #fun);

#define VK_GLOBAL_LEVEL_FUNC_MANDATORY(fun) \
    VK_GLOBAL_LEVEL_FUNC(fun) \
    if(!fun) \
    { \
      fprintf(stderr, "Could not load global Vulkan function: %s !\n", #fun); \
      return false; \
    }

#include "function_list.inl"

    return true;
}

bool loadVulkanEntry()
{
    if (handle == nullptr)
        return false;

    vkGetInstanceProcAddr = GET_VK_ENTRY_POINT(handle);
    if (!vkGetInstanceProcAddr)
    {
        fprintf(stderr, "Could not load Vulkan entry function: vkGetInstanceProcAddr!\n");
        return false;
    }

    return true;
}

bool loadVulkanLibrary()
{
    if (handle != nullptr)
        return true;

    handle = LOAD_VK_LIBRARY(DEFAULT_VK_LIBRARY_PATH);
    if( handle == nullptr )
    {
        fprintf(stderr, "Could not load Vulkan library: %s!\n", DEFAULT_VK_LIBRARY_PATH);
        return false;
    }

    return true;
}

}}} // namespace cv::dnn::vkcom
