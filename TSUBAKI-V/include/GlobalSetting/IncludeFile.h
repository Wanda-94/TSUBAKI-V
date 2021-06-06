#pragma once

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif // WIN32
#include "vulkan/vulkan.hpp"

#include "GLFW/glfw3.h"

#ifdef WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#endif // WIN32

#include "Log/Log.h"