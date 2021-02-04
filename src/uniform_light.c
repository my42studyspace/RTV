/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwhackew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:06:54 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 21:06:57 by mwhackew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_light_uniform_add(t_light light, int index,
GLuint shader_program)
{
	GLuint	i;
	char	*combine;

	combine = combine_str_int_str("lights[", index, "].type");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1i(i, light.type);
	free(combine);
	combine = combine_str_int_str("lights[", index, "].transform.position");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, light.transform.position[0], light.transform.position[1],
	light.transform.position[2]);
	free(combine);
	combine = combine_str_int_str("lights[", index, "].transform.rotation");
	i = glGetUniformLocation(shader_program, combine);
	glUniform3f(i, light.transform.rotation[0], light.transform.rotation[1],
	light.transform.rotation[2]);
	free(combine);
}

void			set_light_uniform(t_light light, int index,
GLuint shader_program)
{
	GLuint		i;
	double		l;
	char		*combine;

	set_light_uniform_add(light, index, shader_program);
	combine = combine_str_int_str("lights[", index, "].direction");
	i = glGetUniformLocation(shader_program, combine);
	l = sqrt(light.direction[0] * light.direction[0] + light.direction[1] *
	light.direction[1] + light.direction[2] * light.direction[2]);
	glUniform3f(i, light.direction[0] / l, light.direction[1] / l,
	light.direction[2] / l);
	free(combine);
	combine = combine_str_int_str("lights[", index, "].intensity");
	i = glGetUniformLocation(shader_program, combine);
	glUniform1f(i, clamp(light.intensity, 0.0, 100.0));
	free(combine);
	if (light.type == POINT)
	{
		combine = combine_str_int_str("lights[", index, "].direction");
		i = glGetUniformLocation(shader_program, combine);
		glUniform3f(i, clamp(light.radius, 0.1, FLOAT_MAX / 10.0), 0.0, 0.0);
		free(combine);
	}
}
