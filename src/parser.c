/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:33:05 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_line(t_rtv1 *rtv1, char **mass)
{
	if ((ft_strcmp("camera:", mass[0])) == 0)
		parse_cam(rtv1, mass);
	else if ((ft_strcmp("light:", mass[0])) == 0)
		parse_light(rtv1, mass);
	else if ((ft_strcmp("sphere:", mass[0])) == 0)
		parse_sphere(rtv1, mass);
	else if ((ft_strcmp("plane:", mass[0])) == 0)
		parse_plane(rtv1, mass);
	else if ((ft_strcmp("cone:", mass[0])) == 0)
		parse_cone(rtv1, mass);
	else if ((ft_strcmp("cylinder:", mass[0])) == 0)
		parse_cylinder(rtv1, mass);
	else
		exit_with_error("invalid scene");
}

void		parser(t_rtv1 *rtv1)
{
	int		n;
	int		fd;
	char	*line;
	char	**mass;

	if (((fd = open(rtv1->argv[1], O_RDONLY)) < 0))
		exit_with_error("invalid file");
	while ((n = get_next_line(fd, &line)))
	{
		if (line[0] == '\0' || line[0] == ' ' || line[0] == '\n')
			exit_with_error("invalid scene");
		if (n < 0)
			exit_with_error("file read error");
		if (!(mass = ft_strsplit(line, ' ')))
			exit_with_error("memory allocation error");
		parse_line(rtv1, mass);
		free_double_char_array(mass);
		if (line)
			free(line);
	}
	close(fd);
}
