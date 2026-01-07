/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:26:25 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/02 13:56:25 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	key_press(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (keycode == KEY_W)
		cub->keys.w = 1;
	if (keycode == KEY_S)
		cub->keys.s = 1;
	if (keycode == KEY_A)
		cub->keys.a = 1;
	if (keycode == KEY_D)
		cub->keys.d = 1;
	if (keycode == KEY_LEFT)
		cub->keys.left = 1;
	if (keycode == KEY_RIGHT)
		cub->keys.right = 1;
	if (keycode == KEY_ESC)
		return (handle_close(param));
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (keycode == KEY_W)
		cub->keys.w = 0;
	if (keycode == KEY_S)
		cub->keys.s = 0;
	if (keycode == KEY_A)
		cub->keys.a = 0;
	if (keycode == KEY_D)
		cub->keys.d = 0;
	if (keycode == KEY_LEFT)
		cub->keys.left = 0;
	if (keycode == KEY_RIGHT)
		cub->keys.right = 0;
	return (0);
}

void	handle_keys(t_cub3d *cub)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.01;
	if (cub->keys.w)
		move_forward(cub, move_speed);
	if (cub->keys.s)
		move_backward(cub, move_speed);
	if (cub->keys.a)
		strafe_left(cub, move_speed);
	if (cub->keys.d)
		strafe_right(cub, move_speed);
	if (cub->keys.left)
		rotate_left(cub, rot_speed);
	if (cub->keys.right)
		rotate_right(cub, rot_speed);
}
