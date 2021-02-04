/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfreddie <gfreddie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:14:02 by gfreddie          #+#    #+#             */
/*   Updated: 2021/02/03 21:32:54 by gfreddie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotation_x(float *v, float angle)
{
	const float		mat[3][3] = {{1.0, 0.0, 0.0},
	{0.0, cosf(angle), -sinf(angle)},
	{0.0, sinf(angle), cosf(angle)}};
	float			new_v[3];

	new_v[0] = v[0];
	new_v[1] = v[1];
	new_v[2] = v[2];
	v[0] = new_v[0] * mat[0][0] + new_v[1] * mat[0][1] + new_v[2] * mat[0][2];
	v[1] = new_v[0] * mat[1][0] + new_v[1] * mat[1][1] + new_v[2] * mat[1][2];
	v[2] = new_v[0] * mat[2][0] + new_v[1] * mat[2][1] + new_v[2] * mat[2][2];
}

void	rotation_y(float *v, float angle)
{
	const float		mat[3][3] = {{cosf(angle), 0.0, sinf(angle)},
	{0.0, 1.0, 0.0},
	{-sinf(angle), 0.0, cosf(angle)}};
	float			new_v[3];

	new_v[0] = v[0];
	new_v[1] = v[1];
	new_v[2] = v[2];
	v[0] = new_v[0] * mat[0][0] + new_v[1] * mat[0][1] + new_v[2] * mat[0][2];
	v[1] = new_v[0] * mat[1][0] + new_v[1] * mat[1][1] + new_v[2] * mat[1][2];
	v[2] = new_v[0] * mat[2][0] + new_v[1] * mat[2][1] + new_v[2] * mat[2][2];
}

void	apply_rotation(float *v, float angle_x, float angle_y)
{
	angle_x = angle_x / 180.0 * M_PI;
	angle_y = angle_y / 180.0 * M_PI;
	rotation_x(v, angle_x);
	rotation_y(v, angle_y);
}

void	rotate_camera_direction(t_rtv1 *rtv1)
{
	reset_camera_direction(rtv1);
	apply_rotation(rtv1->camera_forward, rtv1->camera.transform.rotation[1],
	rtv1->camera.transform.rotation[0]);
	apply_rotation(rtv1->camera_right, rtv1->camera.transform.rotation[1],
	rtv1->camera.transform.rotation[0]);
}

void	move_camera(t_rtv1 *rtv1)
{
	if (rtv1->camera_move_direction[0] != 0 ||
	rtv1->camera_move_direction[1] != 0)
	{
		rotate_camera_direction(rtv1);
		rtv1->camera.transform.position[0] += (rtv1->camera_forward[0] *
		rtv1->camera_move_direction[0] + rtv1->camera_right[0] *
		rtv1->camera_move_direction[1]) * rtv1->camera_move_speed;
		rtv1->camera.transform.position[1] += (rtv1->camera_forward[1] *
		rtv1->camera_move_direction[0] + rtv1->camera_right[1] *
		rtv1->camera_move_direction[1]) * rtv1->camera_move_speed;
		rtv1->camera.transform.position[2] += (rtv1->camera_forward[2] *
		rtv1->camera_move_direction[0] + rtv1->camera_right[2] *
		rtv1->camera_move_direction[1]) * rtv1->camera_move_speed;
	}
}
