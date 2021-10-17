/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:08:44 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/17 20:07:21 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include <string>
#include "Basic_vulk.hpp"

static std::string	info_vendor_id(uint32_t	vendorID)
{
	switch (vendorID)
	{
		case	VK_VENDOR_ID_VIV:
			return "VIV";
			break;

    case	VK_VENDOR_ID_VSI:
			return "VSI";
			break;

    case	VK_VENDOR_ID_KAZAN:
			return "KAZAN";
			break;

    case	VK_VENDOR_ID_CODEPLAY:
			return "CODEPLAY";
			break;

    case	VK_VENDOR_ID_MESA:
			return "MESA";
			break;

    case	VK_VENDOR_ID_POCL:
			return "POCL";
			break;

		default:
			return "UNKNOWN";
	}
}

static std::string	info_phy_dev_type(VkPhysicalDeviceType dev_type)
{
	switch (dev_type)
	{
		case	VK_PHYSICAL_DEVICE_TYPE_OTHER:
			return "Other";
			break;

    case	VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			return "Integrated GPU";
			break;

    case	VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			return "Discrete GPU";
			break;

    case	VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			return "Virtual GPU";
			break;

    case	VK_PHYSICAL_DEVICE_TYPE_CPU:
			return "CPU";
			break;

		default:
			return "UNKNOWN";
	}
}

void	info_physical_device(const VkPhysicalDevice &phy_dev)
{
	VkPhysicalDeviceProperties	dev_props;

	vkGetPhysicalDeviceProperties(phy_dev, &dev_props); //return void
  std::cout << "\t" << dev_props.deviceName << " :" << std::endl;
  std::cout << "\t\tapi version:\t"
		<< VK_API_VERSION_MAJOR(dev_props.apiVersion) 
		<< "." << VK_API_VERSION_MINOR(dev_props.apiVersion) 
		<< "." << VK_API_VERSION_PATCH(dev_props.apiVersion) 
		<< " VARIENT: " << VK_API_VERSION_VARIANT(dev_props.apiVersion) 
		<< std::endl;
  std::cout << "\t\tdriver version:\t" << dev_props.driverVersion << std::endl;
  std::cout << "\t\tvendor id:\t" << info_vendor_id(dev_props.vendorID) << std::endl;
  std::cout << "\t\tdevice id:\t" << dev_props.deviceID << std::endl;
  std::cout << "\t\tdevice type:\t" << info_phy_dev_type(dev_props.deviceType)
		<< std::endl;

	std::cout << std::endl;
}

void  info_vulkan_api_version()
{
	uint32_t	api_version;

	if (VK_RESULT_INFO(vkEnumerateInstanceVersion(&api_version)) != VK_SUCCESS)
		throw std::runtime_error("we're kinda fuck like really fuck damn");
	std::cout << "Vulkan API version: "
		<< VK_API_VERSION_MAJOR(api_version) 
		<< "." << VK_API_VERSION_MINOR(api_version) 
		<< "." << VK_API_VERSION_PATCH(api_version) 
		<< " VARIENT: " << VK_API_VERSION_VARIANT(api_version) 
		<< std::endl << std::endl;
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
