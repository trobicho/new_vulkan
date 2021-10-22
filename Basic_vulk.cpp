/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basic_vulk.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:37:28 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/22 10:54:55 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Basic_vulk.hpp"
#include <iostream>

Basic_vulk::Basic_vulk(GLFWwindow *win, uint32_t win_width, uint32_t win_height
	, uint32_t debug_mode = 0) : m_win(win)
		, m_win_width(win_width)
		, m_win_height(win_height)
		, m_debug_mode(debug_mode)
{
}

Basic_vulk::~Basic_vulk()
{
	vkDestroyPipelineLayout(m_device, m_pipeline_layout, nullptr);
	for (auto image_view : m_image_views)
		vkDestroyImageView(m_device, image_view, nullptr);
	vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
	vkDestroyDevice(m_device, nullptr);
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyInstance(m_instance, nullptr);
	glfwDestroyWindow(m_win);
	glfwTerminate();
}

void  Basic_vulk::init()
{
	create_instance();
	create_surface();
	choose_physical_device();
	create_logical_device();
	create_swapchain();
	create_image_views();
	create_render_pass();
	create_graphics_pipeline();
}

void  Basic_vulk::create_instance()
{
	VkApplicationInfo app_info = {};
	std::vector<const char*>  val_layers = {"VK_LAYER_KHRONOS_validation"};
	std::vector<const char*>  ext;
	uint32_t  ext_count;

	if (m_debug_mode & DEBUG_PRINT_INFO_VK)
		info_vulkan_api_version();
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "Vulkan Basic";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_2;

	VkInstanceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	ext = get_extensions(m_debug_mode, &ext_count);
	if (ext.size() < ext_count)
		throw std::runtime_error("failed to get extensions!");

	create_info.enabledExtensionCount = ext_count;
	create_info.ppEnabledExtensionNames = ext.data();
	create_info.enabledLayerCount = 0;
	if (m_debug_mode & DEBUG_VALIDATION_LAYER)
	{
		if (!val_layer_check(m_debug_mode, val_layers))
			throw std::runtime_error("validation layers requested, but not available!");
		create_info.enabledLayerCount = val_layers.size();
		create_info.ppEnabledLayerNames = val_layers.data();
	}

	if (VK_RESULT_INFO(vkCreateInstance(&create_info, NULL, &m_instance))
			!= VK_SUCCESS)
		throw std::runtime_error("failed to create instance!");
}

void	Basic_vulk::create_logical_device()
{
	VkDeviceCreateInfo				device_create_info = {};
	VkDeviceQueueCreateInfo		queue_create_info = {};
	VkPhysicalDeviceFeatures	device_features = {};
	std::vector<const char*>  ext_names = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	uint32_t	queue_family_index = queue_family(m_physical_device, m_surface);
	if (queue_family_index == MAX_UINT32_T)
		throw std::runtime_error("failed to find valid queue family!");
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = queue_family_index;
	queue_create_info.queueCount = 1;
	float	queue_priority = 1.0f;
	queue_create_info.pQueuePriorities = &queue_priority;

	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.pQueueCreateInfos = &queue_create_info;
	device_create_info.queueCreateInfoCount = 1;
	device_create_info.enabledLayerCount = 0; //Deprecated
	device_create_info.pEnabledFeatures = &device_features;
	device_create_info.enabledExtensionCount = ext_names.size();
	device_create_info.ppEnabledExtensionNames = ext_names.data();
	if (VK_RESULT_INFO(vkCreateDevice(m_physical_device
			, &device_create_info, NULL, &m_device)) != VK_SUCCESS)
		throw std::runtime_error("failed to create device!");
	vkGetDeviceQueue(m_device, queue_family_index, 0, &m_queue_graphics);
}

void	Basic_vulk::create_surface()
{
	if (VK_RESULT_INFO(glfwCreateWindowSurface(m_instance, m_win
			, nullptr, &m_surface))!= VK_SUCCESS)
    throw std::runtime_error("failed to create window surface!");
}

void	Basic_vulk::create_image_views()
{
	m_image_views.resize(m_swapchain_images.size());
	for (size_t i = 0; i < m_swapchain_images.size(); ++i)
	{
		VkImageViewCreateInfo	create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		create_info.image = m_swapchain_images[i];
		create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		create_info.format = m_swapchain_format;
		create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		create_info.subresourceRange.baseMipLevel = 0;
		create_info.subresourceRange.levelCount = 1;
		create_info.subresourceRange.baseArrayLayer = 0;
		create_info.subresourceRange.layerCount = 1;
		if (VK_RESULT_INFO(vkCreateImageView(m_device, &create_info, nullptr
				, &m_image_views[i])) != VK_SUCCESS)
			throw std::runtime_error("failed to create image views");
	}
}

void	Basic_vulk::create_render_pass()
{
}
