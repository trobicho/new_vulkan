/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_phy.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:34:44 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/20 03:35:06 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Basic_vulk.hpp"
#include <iostream>
#include <stdexcept>

static bool	is_device_suitable(const VkPhysicalDevice &phy_dev)
{
	uint32_t	queue_family_count;
	//SWAP_CHAIN_DETAIL vkGetPhysicalDeviceFeatures(device, &dev_feat);

	vkGetPhysicalDeviceQueueFamilyProperties(phy_dev, &queue_family_count, nullptr); //void
	if (queue_family_count == 0)
		return false;
	std::vector<VkQueueFamilyProperties>	queue_family_props(queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(phy_dev
			, &queue_family_count, queue_family_props.data());
	for (const auto & queue : queue_family_props)
	{
		if (queue.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			return (true);
	}
	return (false);
}

void	Basic_vulk::choose_physical_device()
{
	uint32_t	phy_dev_count;

	if (VK_RESULT_INFO(
		vkEnumeratePhysicalDevices(m_instance, &phy_dev_count, nullptr)) != VK_SUCCESS)
    throw std::runtime_error("failed to get physical devices properties");
	std::vector<VkPhysicalDevice>	phy_devices(phy_dev_count);
	if (VK_RESULT_INFO(
		vkEnumeratePhysicalDevices(m_instance, &phy_dev_count, phy_devices.data()))
		!= VK_SUCCESS)
    throw std::runtime_error("failed to get physical devices properties");
	if (m_debug_mode & DEBUG_PRINT_INFO_DEVICE)
	{
		std::cout << "DEVICES INFO (" << phy_dev_count << ")" << ":" << std::endl;
		for(const auto &dev : phy_devices)
		{
			info_physical_device(dev);
			info_queue_family_properties(dev, 2);
		}
	}
	for(const auto &dev : phy_devices)
	{
		VkPhysicalDeviceProperties	dev_props;
		vkGetPhysicalDeviceProperties(dev, &dev_props);
		if (is_device_suitable(dev))
		{
			std::cout << "Choosed device: " << dev_props.deviceName << std::endl;
			m_physical_device = dev;
		}
	}
}
