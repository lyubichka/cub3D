/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:22:57 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:12:21 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	draw_minimap(t_cub3d *cub, t_image *img)
{
	t_minimap_params	params;
	t_minimap_draw		draw;
	t_rect				bg_rect;

	if (!cub || !img)
		return ;
	compute_minimap_params(cub, &params);
	if (params.tile_size == 0)
		return ;
	draw.img = img;
	draw.tile_size = params.tile_size;
	draw.offset_x = params.offset_x;
	draw.offset_y = params.offset_y;
	bg_rect.x = params.offset_x - 2;
	bg_rect.y = params.offset_y - 2;
	bg_rect.w = params.map_px_w + 4;
	bg_rect.h = params.map_px_h + 4;
	draw_filled_rect(img, bg_rect, MINIMAP_BG);
	draw_map_cells(cub, &draw);
	draw_player_on_minimap(cub, &draw);
}
