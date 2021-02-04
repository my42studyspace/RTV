/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwhackew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:06:36 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 21:06:40 by mwhackew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_cylinder_uniform_add(t_cylinder cylinder, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	combine = combine_str_int_str("cylinders[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cylinder.transform.position[0],
	cylinder.transform.position[1], cylinder.transform.position[2]);
	free(combine);
	combine = combine_str_int_str("cylinders[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cylinder.transform.rotation[0],
	cylinder.transform.rotation[1], cylinder.transform.rotation[2]);
	free(combine);
	combine = combine_str_int_str("cylinders[", index, "].axis");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, 0.0, 0.0, 1.0);
	free(combine);
}

void			set_cylinder_uniform(t_cylinder cylinder, int index,
GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	set_cylinder_uniform_add(cylinder, index, shader_program);
	combine = combine_str_int_str("cylinders[", index, "].radius");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(cylinder.radius, 0, FLOAT_MAX / 10.0));
	free(combine);
	combine = combine_str_int_str("cylinders[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cylinder.material.color[0], cylinder.material.color[1],
	cylinder.material.color[2]);
	free(combine);
	combine = combine_str_int_str("cylinders[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(cylinder.material.specular, 0.0, 1000));
	free(combine);
	combine = combine_str_int_str("cylinders[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	free(combine);
}
