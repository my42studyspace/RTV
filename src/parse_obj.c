/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:33:04 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		parse_cam(t_rtv1 *rtv1, char **mass)
{
	char **str;

	if (!(str = ft_strsplit(mass[1], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->camera.transform.position, str);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[2], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->camera.transform.rotation, str);
	free_double_char_array(str);
	rtv1->camera.transform.rotation[1] = -rtv1->camera.
	transform.rotation[1];
	rtv1->camera.direction[0] = 0.0f;
	rtv1->camera.direction[1] = 0.0f;
	rtv1->camera.direction[2] = 1.0f;
	return (0);
}

int		parse_sphere(t_rtv1 *rtv1, char **mass)
{
	char **str;

	rtv1->number_of_spheres++;
	if (!(str = ft_strsplit(mass[1], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->spheres[rtv1->number_of_spheres].transform.position, str);
	free_double_char_array(str);
	rtv1->spheres[rtv1->number_of_spheres].transform.rotation[0] = 0.0f;
	rtv1->spheres[rtv1->number_of_spheres].transform.rotation[1] = 0.0f;
	rtv1->spheres[rtv1->number_of_spheres].transform.rotation[2] = 0.0f;
	if (!(str = ft_strsplit(mass[4], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->spheres[rtv1->number_of_spheres].material.color, str);
	parse_float(&rtv1->spheres[rtv1->number_of_spheres].radius, mass[3]);
	parse_float(&rtv1->spheres[rtv1->number_of_spheres].material.specular,
		mass[5]);
	free_double_char_array(str);
	return (0);
}

int		parse_plane(t_rtv1 *rtv1, char **mass)
{
	char **str;

	rtv1->number_of_planes++;
	if (!(str = ft_strsplit(mass[1], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->planes[rtv1->number_of_planes].transform.position, str);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[2], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->planes[rtv1->number_of_planes].transform.rotation, str);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[3], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->planes[rtv1->number_of_planes].material.color, str);
	parse_float(&rtv1->planes[rtv1->number_of_planes].material.specular,
		mass[4]);
	free_double_char_array(str);
	return (0);
}

int		parse_cone(t_rtv1 *rtv1, char **mass)
{
	char **str;

	rtv1->number_of_cones++;
	if (!(str = ft_strsplit(mass[1], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->cones[rtv1->number_of_cones].transform.position, str);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[2], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->cones[rtv1->number_of_cones].transform.rotation, str);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[4], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->cones[rtv1->number_of_cones].material.color, str);
	parse_float(&rtv1->cones[rtv1->number_of_cones].angle, mass[3]);
	free_double_char_array(str);
	rtv1->cones[rtv1->number_of_cones].material.specular = 0;
	rtv1->cones[rtv1->number_of_cones].axis[0] = 0.0;
	rtv1->cones[rtv1->number_of_cones].axis[1] = 1.0;
	rtv1->cones[rtv1->number_of_cones].axis[2] = 0.0;
	return (0);
}

int		parse_cylinder(t_rtv1 *rtv1, char **mass)
{
	char **str;

	rtv1->number_of_cylinders++;
	if (!(str = ft_strsplit(mass[1], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->cylinders[rtv1->number_of_cylinders].transform.position,
		str);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[2], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->cylinders[rtv1->number_of_cylinders].transform.rotation,
		str);
	parse_float(&rtv1->cylinders[rtv1->number_of_cylinders].radius, mass[3]);
	free_double_char_array(str);
	if (!(str = ft_strsplit(mass[4], ',')))
		exit_with_error("invalid scene");
	parse_vec3(rtv1->cylinders[rtv1->number_of_cylinders].material.color, str);
	parse_float(&rtv1->cylinders[rtv1->number_of_cylinders].material.specular,
		mass[5]);
	rtv1->cylinders[rtv1->number_of_cylinders].axis[0] = 0.0f;
	rtv1->cylinders[rtv1->number_of_cylinders].axis[1] = 1.0f;
	rtv1->cylinders[rtv1->number_of_cylinders].axis[2] = 0.0f;
	free_double_char_array(str);
	return (0);
}
