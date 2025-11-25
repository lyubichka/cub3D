/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:45:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 01:44:29 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	is_valid_pos(t_cub3d *cub, int x, int y)
{
	if (x >= 0 && x < cub->scene.map.width && y >= 0
		&& y < cub->scene.map.height && cub->scene.map.grid[y][x] != '1')
		return (1);
	return (0);
}

void	move_forward(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x + cub->scene.player.dir_x * move_speed;
	new_y = cub->scene.player.pos_y + cub->scene.player.dir_y * move_speed;
	if (is_valid_pos(cub, (int)new_x, (int)cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (is_valid_pos(cub, (int)cub->scene.player.pos_x, (int)new_y))
		cub->scene.player.pos_y = new_y;
}

void	move_backward(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x - cub->scene.player.dir_x * move_speed;
	new_y = cub->scene.player.pos_y - cub->scene.player.dir_y * move_speed;
	if (is_valid_pos(cub, (int)new_x, (int)cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (is_valid_pos(cub, (int)cub->scene.player.pos_x, (int)new_y))
		cub->scene.player.pos_y = new_y;
}

void	strafe_left(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x - cub->scene.player.plane_x * move_speed;
	new_y = cub->scene.player.pos_y - cub->scene.player.plane_y * move_speed;
	if (is_valid_pos(cub, (int)new_x, (int)cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (is_valid_pos(cub, (int)cub->scene.player.pos_x, (int)new_y))
		cub->scene.player.pos_y = new_y;
}

void	strafe_right(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x + cub->scene.player.plane_x * move_speed;
	new_y = cub->scene.player.pos_y + cub->scene.player.plane_y * move_speed;
	if (is_valid_pos(cub, (int)new_x, (int)cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (is_valid_pos(cub, (int)cub->scene.player.pos_x, (int)new_y))
		cub->scene.player.pos_y = new_y;
}
