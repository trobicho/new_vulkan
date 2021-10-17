/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_phy.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:34:44 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/17 20:04:35 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Basic_vulk.hpp"
#include <iostream>


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
		}
	}
}
