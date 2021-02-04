/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_callback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:32:59 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		mouse_button_callback(GLFWwindow *window, int key, int action,
int mode)
{
	t_rtv1 *rtv1;

	rtv1 = (t_rtv1*)glfwGetWindowUserPointer(window);
	mode = sizeof(mode);
	if (key == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &(rtv1->prev_mouse_pos_x),
			&(rtv1->prev_mouse_pos_y));
			rtv1->is_mouse_move = 1;
		}
		else if (action == GLFW_RELEASE)
			rtv1->is_mouse_move = 0;
	}
}

static void	set_move_direction(t_rtv1 *rtv1, int key)
{
	if (key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A ||
	key == GLFW_KEY_D)
		rtv1->is_move = 0;
	if (key == GLFW_KEY_W)
		rtv1->camera_move_direction[0] = 0.0;
	if (key == GLFW_KEY_S)
		rtv1->camera_move_direction[0] = 0.0;
	if (key == GLFW_KEY_D)
		rtv1->camera_move_direction[1] = 0.0;
	if (key == GLFW_KEY_A)
		rtv1->camera_move_direction[1] = 0.0;
}

void		key_callback(GLFWwindow *window, int key, int scancode, int action)
{
	t_rtv1 *rtv1;

	rtv1 = (t_rtv1*)glfwGetWindowUserPointer(window);
	scancode = sizeof(scancode);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_REPEAT || action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_S || key == GLFW_KEY_A ||
		key == GLFW_KEY_D)
			rtv1->is_move = 1;
		if (key == GLFW_KEY_W)
			rtv1->camera_move_direction[0] = 1.0;
		if (key == GLFW_KEY_S)
			rtv1->camera_move_direction[0] = -1.0;
		if (key == GLFW_KEY_D)
			rtv1->camera_move_direction[1] = 1.0;
		if (key == GLFW_KEY_A)
			rtv1->camera_move_direction[1] = -1.0;
	}
	if (action == GLFW_RELEASE)
	{
		set_move_direction(rtv1, key);
	}
}

void		set_event_callbacks(t_rtv1 *rtv1)
{
	glfwSetKeyCallback(rtv1->window,
	(void (*)(struct GLFWwindow *, int, int, int, int))key_callback);
	glfwSetMouseButtonCallback(rtv1->window, mouse_button_callback);
}
