/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:28:16 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/16 22:10:23 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define DEBUG_SHOW_EVERY_RETURN_CODE
#include "Basic_vulk.hpp"
#include <iostream>

static void	main_loop(Basic_vulkan &vulk, GLFWwindow *win)
{
	while(!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
  }
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *win = glfwCreateWindow(800, 800, "Vulkan", NULL, NULL);
  Basic_vulk  vulk(win,
    DEBUG_PRINT_INFO | DEBUG_VALIDATION_LAYER | DEBUG_EXTENSION);

	main_loop(vulk, win);

  return (0);
}
