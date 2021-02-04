/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:05:57 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 21:33:13 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_cone_uniform_add(t_cone cone, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	combine = combine_str_int_str("cones[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cone.transform.position[0], cone.transform.position[1],
	cone.transform.position[2]);
	free(combine);
	combine = combine_str_int_str("cones[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cone.transform.rotation[0], cone.transform.rotation[1],
	cone.transform.rotation[2]);
	free(combine);
	combine = combine_str_int_str("cones[", index, "].axis");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, 0.0, 1.0, 0.0);
	free(combine);
}

void			set_cone_uniform(t_cone cone, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	set_cone_uniform_add(cone, index, shader_program);
	combine = combine_str_int_str("cones[", index, "].angle");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(cone.angle / 180 * M_PI, 0.0001, M_PI_2 - 0.0001));
	free(combine);
	combine = combine_str_int_str("cones[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, cone.material.color[0], cone.material.color[1],
	cone.material.color[2]);
	free(combine);
	combine = combine_str_int_str("cones[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(cone.material.specular, 0.0, 1000.0));
	free(combine);
	combine = combine_str_int_str("cones[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	free(combine);
}
