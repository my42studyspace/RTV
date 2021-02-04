/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:33:04 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_vec3(float *vec3, char **str)
{
	if (str[0] == NULL || str[1] == NULL || str[2] == NULL)
		exit_with_error("invalid scene");
	vec3[0] = (float)atof(str[0]);
	vec3[1] = (float)atof(str[1]);
	vec3[2] = (float)atof(str[2]);
}

void		parse_float(float *f, char *str)
{
	int		i;

	if (str == NULL)
		exit_with_error("invalid scene");
	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
			exit_with_error("invalid scene");
	*f = (float)atof(str);
}

void		parse_light_help(t_rtv1 *rtv1, char **mass)
{
	char	**str;

	rtv1->lights[rtv1->number_of_lights].type = POINT;
	if (!(str = ft_strsplit(mass[2], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->lights[rtv1->number_of_lights].transform.position,
		str);
	parse_float(&rtv1->lights[rtv1->number_of_lights].radius, mass[3]);
	parse_float(&rtv1->lights[rtv1->number_of_lights].intensity, mass[4]);
	free_double_char_array(str);
}

int			parse_light(t_rtv1 *rtv1, char **mass)
{
	char **str;

	rtv1->number_of_lights++;
	if (ft_strcmp(mass[1], "direction") == 0)
	{
		rtv1->lights[rtv1->number_of_lights].type = DIRECTION;
		if (!(str = ft_strsplit(mass[2], ',')))
			exit_with_error("invalid scene");
		parse_vec3(rtv1->lights[rtv1->number_of_lights].direction, str);
		parse_float(&rtv1->lights[rtv1->number_of_lights].intensity, mass[3]);
		free_double_char_array(str);
	}
	else if (ft_strcmp(mass[1], "ambient") == 0)
	{
		rtv1->lights[rtv1->number_of_lights].type = AMBIENT;
		parse_float(&rtv1->lights[rtv1->number_of_lights].intensity, mass[2]);
	}
	else if (ft_strcmp(mass[1], "point") == 0)
		parse_light_help(rtv1, mass);
	else
		exit_with_error("parse light");
	return (0);
}
