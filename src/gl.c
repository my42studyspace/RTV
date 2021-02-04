/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:33:00 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void				create_window(t_rtv1 *rtv1)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	rtv1->window = glfwCreateWindow(WIDTH, HEIGHT, "rtv1", NULL, NULL);
	if (rtv1->window == NULL)
	{
		glfwTerminate();
		exit_with_error("glfw terminate");
	}
	glfwMakeContextCurrent(rtv1->window);
	glfwSetWindowUserPointer(rtv1->window, (void*)rtv1);
}

static void				create_program(t_rtv1 *rtv1)
{
	rtv1->vertex_shader_source = "#version 330 core layout (location = 0) \
	in vec3 position; void main() { gl_Position = vec4(position.x, \
	position.y, position.z, 1.0); }";
	rtv1->fragment_shader_source = load_shader(SHADER_FILE);
	rtv1->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(rtv1->fragment_shader, 1,
	(const GLchar **)&(rtv1->fragment_shader_source), NULL);
	glCompileShader(rtv1->fragment_shader);
	rtv1->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(rtv1->vertex_shader, 1,
	(const GLchar **)&(rtv1->vertex_shader_source), NULL);
	glCompileShader(rtv1->vertex_shader);
	rtv1->shader_program = glCreateProgram();
	glAttachShader(rtv1->shader_program, rtv1->vertex_shader);
	glAttachShader(rtv1->shader_program, rtv1->fragment_shader);
	glLinkProgram(rtv1->shader_program);
	free(rtv1->fragment_shader_source);
	glDeleteShader(rtv1->vertex_shader);
	glDeleteShader(rtv1->fragment_shader);
}

void					init_gl(t_rtv1 *rtv1)
{
	const GLfloat		vertices[] = {1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f};
	const GLuint		indices[] = {0, 1, 3, 1, 2, 3};

	create_window(rtv1);
	set_event_callbacks(rtv1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		exit_with_error("glew");
	create_program(rtv1);
	glGenVertexArrays(1, &(rtv1->vao));
	glGenBuffers(1, &(rtv1->vbo));
	glGenBuffers(1, &(rtv1->ebo));
	glBindVertexArray(rtv1->vao);
	glBindBuffer(GL_ARRAY_BUFFER, rtv1->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rtv1->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
	(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

static void				if_camera_move(t_rtv1 *rtv1)
{
	glfwGetCursorPos(rtv1->window, &(rtv1->cur_mouse_pos_x),
	&(rtv1->cur_mouse_pos_y));
	rtv1->camera.transform.rotation[0] += (rtv1->cur_mouse_pos_x -
	rtv1->prev_mouse_pos_x) * rtv1->camera_rotation_speed;
	rtv1->camera.transform.rotation[1] += (rtv1->cur_mouse_pos_y -
	rtv1->prev_mouse_pos_y) * rtv1->camera_rotation_speed;
	rtv1->prev_mouse_pos_x = rtv1->cur_mouse_pos_x;
	rtv1->prev_mouse_pos_y = rtv1->cur_mouse_pos_y;
}

void					loop(t_rtv1 *rtv1)
{
	glfwPollEvents();
	if (rtv1->is_mouse_move == 1 || rtv1->is_move == 1)
		rtv1->render_type = MIN_RENDER;
	else if (rtv1->render_type != STOP_RENDER)
		rtv1->render_type = FULL_RENDER;
	if (rtv1->render_type == FULL_RENDER || rtv1->render_type == MIN_RENDER)
	{
		if (rtv1->is_mouse_move == 1)
			if_camera_move(rtv1);
		if (rtv1->is_move == 1)
			move_camera(rtv1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(rtv1->shader_program);
		set_settings(rtv1, rtv1->shader_program);
		glBindVertexArray(rtv1->vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(rtv1->window);
		if (rtv1->render_type == FULL_RENDER)
			rtv1->render_type = STOP_RENDER;
	}
}
