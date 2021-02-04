/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:33:01 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	usage(void)
{
	ft_putstr("\nusage: ./RTv1 [file_scene]\n\n");
	ft_putstr("\tvec3 emample: 1.0,-1.0,0.1\n");
	ft_putstr("\tfloat emample: 1.1\n\n");
	ft_putstr("scene pattern:\n\n");
	ft_putstr("\tcamera: [vec3: position] [vec3: rotation]\n");
	ft_putstr("\tlight: direction [vec3: direction] [float: intensity]\n");
	ft_putstr("\tlight: ambient [float: intensity]\n");
	ft_putstr("\tlight: point [vec3: position] [float: radius] \
	[float: intensity]\n");
	ft_putstr("\tsphere: [vec3: position] [vec3: rotation] \
	[float: radius] [vec3: color] [float: specular]\n");
	ft_putstr("\tcone: [vec3: position] [vec3: rotation] \
	[float: angle] [vec3: color] [float: specular]\n");
	ft_putstr("\tcylinder: [vec3: position] [vec3: rotation] \
	[float: radius] [vec3: color] [float: specular]\n");
	ft_putstr("\tplane: [vec3: position] [vec3: rotation] \
	[vec3: color] [float: specular]\n\n");
	exit(0);
}

void	exit_with_error(char *message)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(0);
}

float	clamp(float number, float min, float max)
{
	if (number > max)
		return (max);
	else if (number < min)
		return (min);
	else
		return (number);
}

void	malloc_check(void *data)
{
	if (data == NULL)
		exit_with_error("malloc error");
}

char	*load_shader(char *file)
{
	char	*result;
	int		fd;
	int		i;

	i = 0;
	result = (char*)malloc(12050);
	ft_bzero(result, 12050);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_with_error("shader load");
	read(fd, result, 12050);
	return (result);
}
