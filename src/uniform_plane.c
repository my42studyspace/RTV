/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwhackew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:07:16 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 21:07:22 by mwhackew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_plane_uniform_add(t_plane plane, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	combine = combine_str_int_str("planes[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, plane.transform.position[0], plane.transform.position[1],
	plane.transform.position[2]);
	free(combine);
	combine = combine_str_int_str("planes[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, plane.transform.rotation[0], plane.transform.rotation[1],
	plane.transform.rotation[2]);
	free(combine);
	combine = combine_str_int_str("planes[", index, "].normal");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, 0.0, 0.0, 1.0);
	free(combine);
}

void			set_plane_uniform(t_plane plane, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	set_plane_uniform_add(plane, index, shader_program);
	combine = combine_str_int_str("planes[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, plane.material.color[0], plane.material.color[1],
	plane.material.color[2]);
	free(combine);
	combine = combine_str_int_str("planes[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(plane.material.specular, 0.0, 1000.0));
	free(combine);
	combine = combine_str_int_str("planes[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	free(combine);
}
