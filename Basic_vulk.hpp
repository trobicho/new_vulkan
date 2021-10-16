#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#define DEBUG_PRINT_INFO        0x0001
#define DEBUG_VALIDATION_LAYER  0x0002
#define DEBUG_EXTENSION         0x0004

#define DEBUG_EVERYTHING        0xFFFF

#ifdef DEBUG_SHOW_EVERY_RETURN_CODE
  #define VK_RESULT_INFO(result)  info_vulkan_error_code(result)
#else
  #define VK_RESULT_INFO(result)  (result)
#endif

class Basic_vulk
{
  public:
		Basic_vulk(GLFWwindow *win, debug_mode);
    ~Basic_vulk();
    void  Basic_vulk::init();

  private:
    void  Basic_vulk::create_instance();

		GLFWwindow* const m_win;

    //STATE VARIABLE
    uint32_t          m_debug_mode;

    //VULKAN VARIABLE
		VkInstance        m_instance;
    VkDevice          m_device;
};

//INFO
void      vulkan_api_version_info();
VkResult  info_vulkan_error_code(VK_RESULT error_code);

//VAL_LAYER and EXTENSION
bool  val_layer_check(uint32_t debug, std::vector<const char *> &validation_layers);
std::vector<const char*>  get_extensions(uint32_t debug, uint32_t *ext_count);
