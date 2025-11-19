/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:22:57 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 19:23:19 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void draw_filled_rect(t_image *img, int x0, int y0, int w, int h, int color)
{
	int x;
	int y;

	if (w <= 0 || h <= 0)
		return;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

/* draw a simple DDA line */
static void draw_line(t_image *img, int x0, int y0, int x1, int y1, int color)
{
	double dx;
	double dy;
	double steps;
	double sx;
	double sy;
	double cx;
	double cy;
	int i;

	dx = (double)(x1 - x0);
	dy = (double)(y1 - y0);
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	if (steps < 1.0)
	{
		put_pixel(img, x0, y0, color);
		return;
	}
	sx = dx / steps;
	sy = dy / steps;
	cx = (double)x0;
	cy = (double)y0;
	i = 0;
	while (i <= (int)steps)
	{
		put_pixel(img, (int)round(cx), (int)round(cy), color);
		cx += sx;
		cy += sy;
		i++;
	}
}

/* draw a small filled square centered at cx,cy with radius r */
static void draw_filled_square_centered(t_image *img, int cx, int cy, int r, int color)
{
	int x0;
	int y0;
	int x;
	int y;

	x0 = cx - r;
	y0 = cy - r;
	y = 0;
	while (y < 2 * r + 1)
	{
		x = 0;
		while (x < 2 * r + 1)
		{
			put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

/* compute minimap placement and tile size */
static void compute_minimap_params(t_cub3d *cub,
	int *tile_size, int *offset_x, int *offset_y,
	int *map_px_w, int *map_px_h)
{
	int map_w;
	int map_h;
	int max_w;
	int max_h;
	int ts_w;
	int ts_h;

	map_w = cub->scene.map.width;
	map_h = cub->scene.map.height;
	if (map_w <= 0 || map_h <= 0)
	{
		*tile_size = 0;
		return;
	}
	/* max area roughly 1/4 screen */
	max_w = cub->scene.screen_width / 4;
	max_h = cub->scene.screen_height / 4;
	ts_w = max_w / map_w;
	ts_h = max_h / map_h;
	*tile_size = ts_w < ts_h ? ts_w : ts_h;
	if (*tile_size < 2)
		*tile_size = 2;
	*map_px_w = (*tile_size) * map_w;
	*map_px_h = (*tile_size) * map_h;
	*offset_x = 10;
	*offset_y = cub->scene.screen_height - 10 - *map_px_h;
	if (*offset_y < 10)
		*offset_y = 10;
}

/* draw map cells (walls) onto minimap */
static void draw_map_cells(t_cub3d *cub, t_image *img,
	int tile_size, int offset_x, int offset_y)
{
	int row;
	int col;
	int map_h;
	int map_w;
	int cell_x;
	int cell_y;

	map_w = cub->scene.map.width;
	map_h = cub->scene.map.height;
	row = 0;
	while (row < map_h)
	{
		col = 0;
		while (col < map_w)
		{
			if (cub->scene.map.grid[row][col] == '1')
			{
				cell_x = offset_x + col * tile_size;
				cell_y = offset_y + row * tile_size;
				draw_filled_rect(img, cell_x, cell_y, tile_size, tile_size, MINIMAP_WALL);
			}
			col++;
		}
		row++;
	}
}

/* draw player dot and direction line */
static void draw_player_on_minimap(t_cub3d *cub, t_image *img,
	int tile_size, int offset_x, int offset_y)
{
	double player_cx;
	double player_cy;
	int px;
	int py;
	double dir_len;
	double dir_scale;
	int dir_x_end;
	int dir_y_end;

	player_cx = offset_x + cub->scene.player.pos_x * (double)tile_size;
	player_cy = offset_y + cub->scene.player.pos_y * (double)tile_size;
	px = (int)round(player_cx);
	py = (int)round(player_cy);
	draw_filled_square_centered(img, px, py, tile_size > 4 ? 2 : 1, MINIMAP_PLAYER);
	dir_len = sqrt(cub->scene.player.dir_x * cub->scene.player.dir_x +
	               cub->scene.player.dir_y * cub->scene.player.dir_y);
	if (dir_len == 0.0)
		dir_len = 1.0;
	dir_scale = tile_size * 1.5;
	dir_x_end = (int)round(player_cx + (cub->scene.player.dir_x / dir_len) * dir_scale);
	dir_y_end = (int)round(player_cy + (cub->scene.player.dir_y / dir_len) * dir_scale);
	draw_line(img, px, py, dir_x_end, dir_y_end, MINIMAP_DIR);
}

/* public function: draw minimap (bottom-left) */
void draw_minimap(t_cub3d *cub, t_image *img)
{
	int tile_size;
	int offset_x;
	int offset_y;
	int map_px_w;
	int map_px_h;

	if (!cub || !img)
		return;
	compute_minimap_params(cub, &tile_size, &offset_x, &offset_y,
		&map_px_w, &map_px_h);
	if (tile_size == 0)
		return;
	/* background */
	draw_filled_rect(img, offset_x - 2, offset_y - 2, map_px_w + 4, map_px_h + 4, MINIMAP_BG);
	draw_map_cells(cub, img, tile_size, offset_x, offset_y);
	draw_player_on_minimap(cub, img, tile_size, offset_x, offset_y);
}
