/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:28:16 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/25 15:42:25 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Basic_vulk.hpp"
#include <iostream>
#include <chrono>
#include <glm/gtx/transform.hpp>

int width = 1920;
int height = 1080;

s_frag_shader_constant constants;

static void	constants_init()
{
	constants.min = glm::dvec2(-4.055f, -2.0f);
	constants.max = glm::dvec2(3.055f, 2.0f);
	constants.max_iter = 1000;
}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
	double	xpos, ypos;
	glfwGetCursorPos(win, &xpos, &ypos);
	double zoom = 1.0f + (double)(-yoffset) / 20.0;
	glm::dvec2	pos = glm::dvec2(xpos / (double)width
		, ypos / (double)height);
	pos = pos * (constants.max - constants.min) + constants.min;
	constants.min = (constants.min - pos) * (zoom) + pos;
	constants.max = (constants.max - pos) * (zoom) + pos;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_EQUAL && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		constants.max_iter += 100;
		std::cout << "Max Iter: " << constants.max_iter << std::endl;
	}
	if (key == GLFW_KEY_MINUS && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		constants.max_iter -= 100;
		std::cout << "Max Iter: " << constants.max_iter << std::endl;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, GL_TRUE);
	}
}

static void	main_loop(Basic_vulk &vulk, GLFWwindow *win)
{
	auto	first_time = std::chrono::high_resolution_clock::now();
	while(!glfwWindowShouldClose(win))
	{
		auto	time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time_span = time - first_time;
		constants.time = static_cast<float>(time_span.count());
		vulk.update_constant(constants);
		glfwPollEvents();
		vulk.draw_frame();
	}
	vulk.wait_idle();
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *win = glfwCreateWindow(width, height, "Vulkan", NULL, NULL);
	Basic_vulk  vulk(win, width, height,
			DEBUG_PRINT_INFO_ALL | DEBUG_VALIDATION_LAYER | DEBUG_EXTENSION);

	vulk.init();
	constants_init();
	glfwSetScrollCallback(win, scroll_callback);
	glfwSetKeyCallback(win, key_callback);
	main_loop(vulk, win);

	return (0);
}
