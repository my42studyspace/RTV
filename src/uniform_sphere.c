/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwhackew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:07:33 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 21:07:36 by mwhackew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_sphere_uniform_add(t_sphere sphere, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	combine = combine_str_int_str("spheres[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, sphere.transform.position[0],
	sphere.transform.position[1], sphere.transform.position[2]);
	free(combine);
	combine = combine_str_int_str("spheres[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, sphere.transform.rotation[0], sphere.transform.rotation[1],
	sphere.transform.rotation[2]);
	free(combine);
	combine = combine_str_int_str("spheres[", index, "].radius");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(sphere.radius, 0.1, FLOAT_MAX / 10.0));
	free(combine);
}

void			set_sphere_uniform(t_sphere sphere, int index,
GLuint shader_program)
{
	GLuint		i;
	char		*combine;

	set_sphere_uniform_add(sphere, index, shader_program);
	combine = combine_str_int_str("spheres[", index, "].material.color");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, sphere.material.color[0], sphere.material.color[1],
	sphere.material.color[2]);
	free(combine);
	combine = combine_str_int_str("spheres[", index, "].material.specular");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(sphere.material.specular, 0.0, 1000.0));
	free(combine);
	combine = combine_str_int_str("spheres[", index, "].material.reflection");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, 0.1);
	free(combine);
	combine = combine_str_int_str("spheres[", index, "].isOutline");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, sphere.is_outline);
	free(combine);
	combine = combine_str_int_str("spheres[", index, "].isToon");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, sphere.is_toon);
	free(combine);
}
