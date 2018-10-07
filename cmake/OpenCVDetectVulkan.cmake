set(VULKAN_INCLUDE_DIRS "${OpenCV_SOURCE_DIR}/modules/dnn/src/vkcom/" CACHE PATH "Vulkan include directory")
set(VULKAN_LIBRARIES "")

try_compile(VALID_VULKAN
      "${OpenCV_BINARY_DIR}"
      "${OpenCV_SOURCE_DIR}/cmake/checks/vulkan.cpp"
      CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${VULKAN_INCLUDE_DIRS}"
      OUTPUT_VARIABLE TRY_OUT
      )
if(NOT ${VALID_VULKAN})
  message(WARNING "Can't use Vulkan")
  return()
endif()

set(HAVE_VULKAN 1)
add_definitions(-DVK_NO_PROTOTYPES)
include_directories(${VULKAN_INCLUDE_DIRS})


#if(NOT HAVE_VULKAN)
#  set(CMAKE_MODULE_PATH "${OpenCV_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
#  find_package(Vulkan) # Try CMake-based config files
#  if(Vulkan_FOUND)
#    set(VULKAN_INCLUDE_DIRS "${Vulkan_INCLUDE_DIRS}" CACHE PATH "Vulkan include directories" FORCE)
#    set(VULKAN_LIBRARIES "${Vulkan_LIBRARIES}" CACHE PATH "Vulkan libraries" FORCE)
#    set(HAVE_VULKAN 1)
#  endif()
#endif()
#
#if(HAVE_VULKAN)
#  include_directories(${VULKAN_INCLUDE_DIRS})
#  list(APPEND OPENCV_LINKER_LIBS ${VULKAN_LIBRARIES})
#  add_definitions(-DVK_NO_PROTOTYPES)
#else()
#  ocv_clear_vars(VULKAN_INCLUDE_DIRS VULKAN_LIBRARIES)
#endif()
