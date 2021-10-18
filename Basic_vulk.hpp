#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>

#define DEBUG_PRINT_INFO_VK       0x0001
#define DEBUG_PRINT_INFO_DEVICE   0x0002
#define DEBUG_PRINT_INFO_ALL      0x000F

#define DEBUG_VALIDATION_LAYER    0x0010
#define DEBUG_EXTENSION           0x0020

#define DEBUG_EVERYTHING          0xFFFF

#define DEBUG_SHOW_EVERY_RETURN_CODE

#ifdef DEBUG_SHOW_EVERY_RETURN_CODE
#define VK_RESULT_INFO(result)  (info_vulkan_error_code(result))
#else
#define VK_RESULT_INFO(result)  (result)
#endif

class Basic_vulk
{
	public:
		Basic_vulk(GLFWwindow *win, uint32_t debug_mode);
		~Basic_vulk();
		void  init();

	private:
		void  create_instance();
		void	choose_physical_device();

		GLFWwindow* const m_win;

		//STATE VARIABLE
		uint32_t          m_debug_mode;

		//VULKAN VARIABLE
		VkInstance        m_instance;
		VkPhysicalDevice	m_physical_device;
		VkDevice          m_device;
};

//VAL_LAYER and EXTENSION
bool	val_layer_check(uint32_t debug, std::vector<const char *> &validation_layers);
std::vector<const char*>  get_extensions(uint32_t debug, uint32_t *ext_count);

//INFO
void			info_vulkan_api_version();
VkResult	info_vulkan_error_code(VkResult error_code);
void			info_physical_device(const VkPhysicalDevice &phy_dev, int tab = 1);
void			info_queue_family_properties(const VkPhysicalDevice &phy_dev, int tab = 1);

