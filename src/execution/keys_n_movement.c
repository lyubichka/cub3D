/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_n_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:26:25 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 00:31:04 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int key_press(int keycode, void *param)
{
	t_cub3d *cub = (t_cub3d *)param;

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
	{ 
		mlx_destroy_window(cub->mlx, cub->win);
		free(cub);
		exit(0);
	}
	return (0);
}

int key_release(int keycode, void *param)
{
	t_cub3d *cub = (t_cub3d *)param;

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

void handle_keys(t_cub3d *cub)
{
	double moveSpeed;
	double rotSpeed;
	double newX;
	double newY;
	double oldDirX;
	double oldPlaneX;

	/* speeds - tune to taste */
	moveSpeed = 0.09;   /* per frame */
	rotSpeed = 0.05;    /* radians per frame */

	/* forward */
	if (cub->keys.w)
	{
		newX = cub->scene.player.pos_x + cub->scene.player.dir_x * moveSpeed;
		newY = cub->scene.player.pos_y + cub->scene.player.dir_y * moveSpeed;
		/* collision: check separately to avoid corner sticking */
		if (cub->scene.map.grid[(int)cub->scene.player.pos_y][(int)newX] != '1')
			cub->scene.player.pos_x = newX;
		if (cub->scene.map.grid[(int)newY][(int)cub->scene.player.pos_x] != '1')
			cub->scene.player.pos_y = newY;
	}

	/* backward */
	if (cub->keys.s)
	{
		newX = cub->scene.player.pos_x - cub->scene.player.dir_x * moveSpeed;
		newY = cub->scene.player.pos_y - cub->scene.player.dir_y * moveSpeed;
		if (cub->scene.map.grid[(int)cub->scene.player.pos_y][(int)newX] != '1')
			cub->scene.player.pos_x = newX;
		if (cub->scene.map.grid[(int)newY][(int)cub->scene.player.pos_x] != '1')
			cub->scene.player.pos_y = newY;
	}

	/* strafe left (perpendicular) */
	if (cub->keys.a)
	{
		newX = cub->scene.player.pos_x - cub->scene.player.plane_x * moveSpeed;
		newY = cub->scene.player.pos_y - cub->scene.player.plane_y * moveSpeed;
		if (cub->scene.map.grid[(int)cub->scene.player.pos_y][(int)newX] != '1')
			cub->scene.player.pos_x = newX;
		if (cub->scene.map.grid[(int)newY][(int)cub->scene.player.pos_x] != '1')
			cub->scene.player.pos_y = newY;
	}

	/* strafe right */
	if (cub->keys.d)
	{
		newX = cub->scene.player.pos_x + cub->scene.player.plane_x * moveSpeed;
		newY = cub->scene.player.pos_y + cub->scene.player.plane_y * moveSpeed;
		if (cub->scene.map.grid[(int)cub->scene.player.pos_y][(int)newX] != '1')
			cub->scene.player.pos_x = newX;
		if (cub->scene.map.grid[(int)newY][(int)cub->scene.player.pos_x] != '1')
			cub->scene.player.pos_y = newY;
	}

	/* rotate left */
	if (cub->keys.left)
	{
		oldDirX = cub->scene.player.dir_x;
		cub->scene.player.dir_x = cub->scene.player.dir_x * cos(rotSpeed) -
			cub->scene.player.dir_y * sin(rotSpeed);
		cub->scene.player.dir_y = oldDirX * sin(rotSpeed) + cub->scene.player.dir_y * cos(rotSpeed);
		oldPlaneX = cub->scene.player.plane_x;
		cub->scene.player.plane_x = cub->scene.player.plane_x * cos(rotSpeed) -
			cub->scene.player.plane_y * sin(rotSpeed);
		cub->scene.player.plane_y = oldPlaneX * sin(rotSpeed) + cub->scene.player.plane_y * cos(rotSpeed);
	}

	/* rotate right */
	if (cub->keys.right)
	{
		oldDirX = cub->scene.player.dir_x;
		cub->scene.player.dir_x = cub->scene.player.dir_x * cos(-rotSpeed) -
			cub->scene.player.dir_y * sin(-rotSpeed);
		cub->scene.player.dir_y = oldDirX * sin(-rotSpeed) + cub->scene.player.dir_y * cos(-rotSpeed);
		oldPlaneX = cub->scene.player.plane_x;
		cub->scene.player.plane_x = cub->scene.player.plane_x * cos(-rotSpeed) -
			cub->scene.player.plane_y * sin(-rotSpeed);
		cub->scene.player.plane_y = oldPlaneX * sin(-rotSpeed) + cub->scene.player.plane_y * cos(-rotSpeed);
	}
}


