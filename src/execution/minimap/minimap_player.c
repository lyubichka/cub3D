/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:12:15 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static void	calculate_player_center(t_cub3d *cub, t_minimap_draw *draw,
		t_point *center)
{
	double	player_cx;
	double	player_cy;
	int		radius;

	player_cx = draw->offset_x + cub->scene.player.pos_x
		* (double)draw->tile_size;
	player_cy = draw->offset_y + cub->scene.player.pos_y
		* (double)draw->tile_size;
	center->x = (int)round(player_cx);
	center->y = (int)round(player_cy);
	if (draw->tile_size > 4)
		radius = 2;
	else
		radius = 1;
	center->radius = radius;
}

static void	calculate_direction_end(t_cub3d *cub, t_point center, int tile_size,
		t_line *line)
{
	double	dir_len;
	double	dir_scale;

	dir_len = sqrt(cub->scene.player.dir_x * cub->scene.player.dir_x
			+ cub->scene.player.dir_y * cub->scene.player.dir_y);
	if (dir_len == 0.0)
		dir_len = 1.0;
	dir_scale = tile_size * 1.5;
	line->x0 = center.x;
	line->y0 = center.y;
	line->x1 = (int)round((double)center.x + (cub->scene.player.dir_x / dir_len)
			* dir_scale);
	line->y1 = (int)round((double)center.y + (cub->scene.player.dir_y / dir_len)
			* dir_scale);
}

void	draw_player_on_minimap(t_cub3d *cub, t_minimap_draw *draw)
{
	t_point	center;
	t_line	dir_line;

	calculate_player_center(cub, draw, &center);
	draw_filled_square_centered(draw->img, center, MINIMAP_PLAYER);
	calculate_direction_end(cub, center, draw->tile_size, &dir_line);
	draw_line(draw->img, dir_line, MINIMAP_DIR);
}
