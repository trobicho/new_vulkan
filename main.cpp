/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:28:16 by trobicho          #+#    #+#             */
/*   Updated: 2021/10/16 23:20:53 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Basic_vulk.hpp"
#include <iostream>

static void	main_loop(Basic_vulk &vulk, GLFWwindow *win)
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

  vulk.init();
	main_loop(vulk, win);

  return (0);
}
