/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:05:00 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/10 20:06:39 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	is_clear_tile(t_cub3d *cub, int x, int y)
{
	if (x < 0 || x >= cub->scene.map.width || y < 0
		|| y >= cub->scene.map.height)
		return (0);
	return (cub->scene.map.grid[y][x] != '1');
}

int	has_player_space(t_cub3d *cub, double x, double y)
{
	const double	radius = 0.18;
	int				tx;
	int				ty;

	tx = (int)(x - radius);
	ty = (int)(y - radius);
	if (!is_clear_tile(cub, tx, ty))
		return (0);
	tx = (int)(x + radius);
	ty = (int)(y - radius);
	if (!is_clear_tile(cub, tx, ty))
		return (0);
	tx = (int)(x - radius);
	ty = (int)(y + radius);
	if (!is_clear_tile(cub, tx, ty))
		return (0);
	tx = (int)(x + radius);
	ty = (int)(y + radius);
	if (!is_clear_tile(cub, tx, ty))
		return (0);
	return (1);
}
