/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:08:44 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/16 23:21:36 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include "Basic_vulk.hpp"

void  info_vulkan_api_version()
{
  uint32_t  api_version;

  if (VK_RESULT_INFO(vkEnumerateInstanceVersion(&api_version)) != VK_SUCCESS)
    throw std::runtime_error("we're kinda fuck like really fuck damn");
  std::cout << "Vulkan API version: "
    << VK_API_VERSION_MAJOR(api_version) 
    << "." << VK_API_VERSION_MINOR(api_version) 
    << "." << VK_API_VERSION_PATCH(api_version) 
    << " VARIENT: " << VK_API_VERSION_VARIANT(api_version) 
    << std::endl;
}

VkResult  info_vulkan_error_code(VkResult error_code)
{
  switch(error_code)
  {
    case VK_SUCCESS:
      //std::cout << "success" << std::endl;
      break;

    case VK_NOT_READY:
      std::cout << "not ready" << std::endl;
      break;

    case VK_TIMEOUT:
      std::cout << "timeout" << std::endl;
      break;

    case VK_EVENT_SET:
      std::cout << "event set" << std::endl;
      break;

    case VK_EVENT_RESET:
      std::cout << "event reset" << std::endl;
      break;

    case VK_INCOMPLETE:
      std::cout << "incomplete" << std::endl;
      break;

    case VK_ERROR_OUT_OF_HOST_MEMORY:
      std::cout << "error out of host memory" << std::endl;
      break;

    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      std::cout << "error out of device memory" << std::endl;
      break;

    case VK_ERROR_INITIALIZATION_FAILED:
      std::cout << "error initialization failed" << std::endl;
      break;

    case VK_ERROR_DEVICE_LOST:
      std::cout << "error device lost" << std::endl;
      break;

    case VK_ERROR_MEMORY_MAP_FAILED:
      std::cout << "error memory map failed" << std::endl;
      break;

    case VK_ERROR_LAYER_NOT_PRESENT:
      std::cout << "error layer not present" << std::endl;
      break;

    case VK_ERROR_EXTENSION_NOT_PRESENT:
      std::cout << "error extension not present" << std::endl;
      break;

    case VK_ERROR_FEATURE_NOT_PRESENT:
      std::cout << "error feature not present" << std::endl;
      break;

    case VK_ERROR_INCOMPATIBLE_DRIVER:
      std::cout << "error incompatible driver" << std::endl;
      break;

    case VK_ERROR_TOO_MANY_OBJECTS:
      std::cout << "error too many objects" << std::endl;
      break;

    case VK_ERROR_FORMAT_NOT_SUPPORTED:
      std::cout << "error format not supported" << std::endl;
      break;

    case VK_ERROR_FRAGMENTED_POOL:
      std::cout << "error fragmented pool" << std::endl;
      break;

    case VK_ERROR_UNKNOWN:
      std::cout << "error unknown" << std::endl;
      break;

    case VK_ERROR_OUT_OF_POOL_MEMORY:
      std::cout << "error out of pool memory" << std::endl;
      break;

    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
      std::cout << "error invalid external handle" << std::endl;
      break;

    case VK_ERROR_FRAGMENTATION:
      std::cout << "error fragmentation" << std::endl;
      break;

    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
      std::cout << "error invalid opaque capture address" << std::endl;
      break;

    case VK_ERROR_SURFACE_LOST_KHR:
      std::cout << "error surface lost KHR" << std::endl;
      break;

    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
      std::cout << "error native window in use KHR" << std::endl;
      break;

    case VK_SUBOPTIMAL_KHR:
      std::cout << "error suboptimal KHR" << std::endl;
      break;

    case VK_ERROR_OUT_OF_DATE_KHR:
      std::cout << "error out of date KHR" << std::endl;
      break;

    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
      std::cout << "error incompatible display KHR" << std::endl;
      break;

    case VK_ERROR_VALIDATION_FAILED_EXT:
      std::cout << "error validation failed EXT" << std::endl;
      break;

    case VK_ERROR_INVALID_SHADER_NV:
      std::cout << "error invalid shader NV" << std::endl;
      break;

    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
      std::cout << "error invalid DRM format modifier plane layout EXT" << std::endl;
      break;

    case VK_ERROR_NOT_PERMITTED_EXT:
      std::cout << "error not permitted EXT" << std::endl;
      break;

    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
      std::cout << "error full screen exclusive mode lost EXT" << std::endl;
      break;

    case VK_THREAD_IDLE_KHR:
      std::cout << "error thread idle KHR" << std::endl;
      break;

    case VK_THREAD_DONE_KHR:
      std::cout << "error thread done KHR" << std::endl;
      break;

    case VK_OPERATION_DEFERRED_KHR:
      std::cout << "error operation deferred KHR" << std::endl;
      break;

    case VK_OPERATION_NOT_DEFERRED_KHR:
      std::cout << "error operation not deferred KHR" << std::endl;
      break;

    case VK_PIPELINE_COMPILE_REQUIRED_EXT:
      std::cout << "error pipeline compile required EXT" << std::endl;
      break;

    default:
      std::cout << "undefined error code" << std::endl;
      break;

  }
  return error_code;
}
