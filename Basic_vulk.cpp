/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basic_vulk.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:37:28 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/16 22:08:18 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Basic_vulk.hpp"
#include <iostream>
#include <vector>


Basic_vulk::Basic_vulk(GLFWwindow *win, debug_mode = 0x0) :
  m_win(win), m_debug_mode(debug_mode)
{
}

Basic_vulk::~Basic_vulk()
{
	vkDestroyInstance(m_instance, nullptr);
	glfwDestroyWindow(m_win);
	glfwTerminate();
}

void  Basic_vulk::init()
{
}

void  Basic_vulk::create_instance();
{
	VkApplicationInfo app_info = {};
	std::vector<const char*>  val_layer = {"VK_LAYER_KHRONOS_validation"};
	char      **ext;
	uint32_t  ext_count;

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
	if (ext == nullptr && ext_count > 0)
    throw std::runtime_error("failed to get extensions!");

	create_info.enabledExtensionCount = ext_count;
	create_info.ppEnabledExtensionNames = ext;
	create_info.enabledLayerCount = 0;
	if (m_debug_mode & DEBUG_VALIDATION_LAYER)
	{
		if (!val_layer_check(m_debug_mode, val_layer))
      throw std::runtime_error("validation layers requested, but not available!");
		create_info.enabledLayerCount = val_layer_count;
		create_info.ppEnabledLayerNames = val_layer;
	}

	if (VK_RESULT_INFO(vkCreateInstance(&create_info, NULL, &m_instance)
    != VK_SUCCESS))
    throw std::runtime_error("failed to create instance!");
}
