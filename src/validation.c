/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwhackew <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:59:37 by mwhackew          #+#    #+#             */
/*   Updated: 2021/02/03 20:59:52 by mwhackew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		validate_light(char *str1, char *str2)
{
	if (ft_strcmp(str2, "light:") && (ft_strcmp(str1, "point") == 0 ||
		ft_strcmp(str1, "ambient") == 0 || ft_strcmp(str1, "direction") == 0))
		return (1);
	return (0);
}

int		validation_obj(char *line)
{
	char	**mass;
	int		i;
	int		j;

	j = 1;
	mass = ft_strsplit(line, ',');
	while (mass[j])
	{
		i = 0;
		while (mass[j][i])
		{
			if ((validate_light(mass[j], mass[0])) == 1)
				j++;
			else if ((ft_isdigit(mass[j][i])) == 0 && mass[j][i] !=
				'.' && mass[j][i] != '-')
				exit_with_error("invalid scene");
			i++;
		}
		j++;
	}
	ft_strdel(mass);
	return (1);
}

int		validation(char *line)
{
	char	**mass;
	int		i;
	int		j;

	j = 1;
	while ((mass = ft_strsplit(line, ' ')))
	{
		if (ft_strcmp(mass[0], "camera:") == 0 ||
		ft_strcmp(mass[0], "sphere:") == 0 || ft_strcmp(mass[0], "plane:") == 0
		|| ft_strcmp(mass[0], "cone:") == 0 ||
		ft_strcmp(mass[0], "cylinder:") == 0 ||
		ft_strcmp(mass[0], "light:") == 0)
		{
			i = 1;
			while (mass[i] != 0)
			{
				if ((validation_obj(mass[i++])) == 0)
					j = 0;
			}
			if (j == 1)
				return (1);
		}
	}
	ft_strdel(mass);
	return (0);
}
