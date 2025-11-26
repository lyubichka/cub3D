/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:12:18 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static int	calculate_tile_size(int map_w, int map_h, t_minimap_max max)
{
	int	ts_w;
	int	ts_h;
	int	tile_size;

	ts_w = max.max_w / map_w;
	ts_h = max.max_h / map_h;
	if (ts_w < ts_h)
		tile_size = ts_w;
	else
		tile_size = ts_h;
	if (tile_size < 2)
		tile_size = 2;
	return (tile_size);
}

void	compute_minimap_params(t_cub3d *cub, t_minimap_params *params)
{
	t_minimap_max	max;
	int				map_w;
	int				map_h;

	map_w = cub->scene.map.width;
	map_h = cub->scene.map.height;
	if (map_w <= 0 || map_h <= 0)
	{
		params->tile_size = 0;
		return ;
	}
	max.max_w = cub->scene.screen_width / 4;
	max.max_h = cub->scene.screen_height / 4;
	params->tile_size = calculate_tile_size(map_w, map_h, max);
	params->map_px_w = params->tile_size * map_w;
	params->map_px_h = params->tile_size * map_h;
	params->offset_x = 10;
	params->offset_y = cub->scene.screen_height - 10 - params->map_px_h;
	if (params->offset_y < 10)
		params->offset_y = 10;
}

void	draw_map_cells(t_cub3d *cub, t_minimap_draw *draw)
{
	int		row;
	int		col;
	t_rect	rect;

	row = 0;
	while (row < cub->scene.map.height)
	{
		col = 0;
		while (col < cub->scene.map.width)
		{
			if (cub->scene.map.grid[row][col] == '1')
			{
				rect.x = draw->offset_x + col * draw->tile_size;
				rect.y = draw->offset_y + row * draw->tile_size;
				rect.w = draw->tile_size;
				rect.h = draw->tile_size;
				draw_filled_rect(draw->img, rect, MINIMAP_WALL);
			}
			col++;
		}
		row++;
	}
}
