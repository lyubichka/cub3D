/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:45:00 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/10 20:07:09 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	move_forward(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x + cub->scene.player.dir_x * move_speed;
	new_y = cub->scene.player.pos_y + cub->scene.player.dir_y * move_speed;
	if (has_player_space(cub, new_x, cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (has_player_space(cub, cub->scene.player.pos_x, new_y))
		cub->scene.player.pos_y = new_y;
}

void	move_backward(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x - cub->scene.player.dir_x * move_speed;
	new_y = cub->scene.player.pos_y - cub->scene.player.dir_y * move_speed;
	if (has_player_space(cub, new_x, cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (has_player_space(cub, cub->scene.player.pos_x, new_y))
		cub->scene.player.pos_y = new_y;
}

void	strafe_left(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x - cub->scene.player.plane_x * move_speed;
	new_y = cub->scene.player.pos_y - cub->scene.player.plane_y * move_speed;
	if (has_player_space(cub, new_x, cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (has_player_space(cub, cub->scene.player.pos_x, new_y))
		cub->scene.player.pos_y = new_y;
}

void	strafe_right(t_cub3d *cub, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = cub->scene.player.pos_x + cub->scene.player.plane_x * move_speed;
	new_y = cub->scene.player.pos_y + cub->scene.player.plane_y * move_speed;
	if (has_player_space(cub, new_x, cub->scene.player.pos_y))
		cub->scene.player.pos_x = new_x;
	if (has_player_space(cub, cub->scene.player.pos_x, new_y))
		cub->scene.player.pos_y = new_y;
}
