/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwhackew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:05:11 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 21:05:24 by mwhackew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char	*combine_str_int_str(char *str1, int number, char *str2)
{
	size_t	len[3];
	char	*ntos;
	char	*result;

	ntos = ft_itoa(number);
	len[0] = ft_strlen(str1);
	len[1] = ft_strlen(ntos);
	len[2] = ft_strlen(str2);
	result = ft_strnew(len[0] + len[1] + len[2]);
	ft_memcpy(result, str1, len[0]);
	ft_memcpy(result + len[0], ntos, len[1]);
	ft_memcpy(result + (len[0] + len[1]), str2, len[2]);
	ft_strdel(&ntos);
	return (result);
}

void	set_main_settings(GLuint shader_program, t_rtv1 *rtv1)
{
	GLint i;

	i = glGetUniformLocation(shader_program, "resolution");
	glUniform2f(i, (GLfloat)WIDTH, (GLfloat)HEIGHT);
	i = glGetUniformLocation(shader_program, "render_type");
	glUniform1i(i, rtv1->render_type);
}

void	set_objects_count(GLuint shader_program, t_rtv1 *rtv1)
{
	GLuint i;

	i = glGetUniformLocation(shader_program, "CONE_COUNT");
	glUniform1i(i, rtv1->number_of_cones + 1);
	i = glGetUniformLocation(shader_program, "CYLINDER_COUNT");
	glUniform1i(i, rtv1->number_of_cylinders + 1);
	i = glGetUniformLocation(shader_program, "PLANE_COUNT");
	glUniform1i(i, rtv1->number_of_planes + 1);
	i = glGetUniformLocation(shader_program, "SPHERE_COUNT");
	glUniform1i(i, rtv1->number_of_spheres + 1);
	i = glGetUniformLocation(shader_program, "LIGHT_COUNT");
	glUniform1i(i, rtv1->number_of_lights + 1);
}

void	set_cam_uniform(t_camera camera, GLuint shader_program)
{
	GLuint i;

	i = glGetUniformLocation(shader_program, "camera.direction");
	glUniform3f(i, 0.0, 0.0, 1.0);
	i = glGetUniformLocation(shader_program, "camera.transform.position");
	glUniform3f(i, camera.transform.position[0], camera.transform.position[1],
	camera.transform.position[2]);
	i = glGetUniformLocation(shader_program, "camera.transform.rotation");
	glUniform3f(i, camera.transform.rotation[0], camera.transform.rotation[1],
	camera.transform.rotation[2]);
}

void	set_settings(t_rtv1 *rtv1, GLuint shader_program)
{
	int i;

	set_main_settings(shader_program, rtv1);
	set_cam_uniform(rtv1->camera, shader_program);
	set_objects_count(shader_program, rtv1);
	i = -1;
	while (i++ <= rtv1->number_of_lights && i < 16)
		set_light_uniform(rtv1->lights[i], i, shader_program);
	i = -1;
	while (i++ <= rtv1->number_of_spheres && i < 16)
		set_sphere_uniform(rtv1->spheres[i], i, shader_program);
	i = -1;
	while (i++ <= rtv1->number_of_cones && i < 16)
		set_cone_uniform(rtv1->cones[i], i, shader_program);
	i = -1;
	while (i++ <= rtv1->number_of_cylinders && i < 16)
		set_cylinder_uniform(rtv1->cylinders[i], i, shader_program);
	i = -1;
	while (i++ <= rtv1->number_of_spheres && i < 16)
		set_sphere_uniform(rtv1->spheres[i], i, shader_program);
	i = -1;
	while (i++ <= rtv1->number_of_planes && i < 16)
		set_plane_uniform(rtv1->planes[i], i, shader_program);
}
