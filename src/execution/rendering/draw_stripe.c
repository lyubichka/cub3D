/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stripe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:08:11 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static void	draw_ceiling(t_image *img, int x, int draw_start, int ceiling_color)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(img, x, y, ceiling_color);
		y++;
	}
}

static void	draw_floor(t_image *img, t_draw_stripe *ds, int floor_color)
{
	int	y;

	y = ds->ray->draw_end + 1;
	while (y < ds->screen_h)
	{
		put_pixel(img, ds->x, y, floor_color);
		y++;
	}
}

static void	draw_wall_texture(t_image *img, t_draw_stripe *ds)
{
	int	y;
	int	tex_y;
	int	color;

	y = ds->ray->draw_start;
	while (y <= ds->ray->draw_end)
	{
		tex_y = (int)ds->params->tex_pos & (ds->params->tex->height - 1);
		color = get_tex_color(ds->params->tex, ds->params->tex_x, tex_y);
		if (ds->ray->side == 1)
			color = ((color >> 1) & 0x7F7F7F);
		put_pixel(img, ds->x, y, color);
		ds->params->tex_pos += ds->params->step;
		y++;
	}
}

void	draw_vertical_stripe_textured(t_image *img, t_cub3d *cub, int x,
		t_ray *ray)
{
	t_tex_params	params;
	t_draw_stripe	ds;
	double			wall_x;

	params.tex = &cub->textures[get_texture_index(ray)];
	wall_x = calc_wall_x(cub, ray);
	params.tex_x = calc_tex_x(wall_x, params.tex, ray);
	init_texture_params(cub, ray, &params);
	ds.x = x;
	ds.ray = ray;
	ds.params = &params;
	ds.screen_h = cub->scene.screen_height;
	draw_ceiling(img, x, ray->draw_start, cub->scene.colors.ceiling_color);
	draw_wall_texture(img, &ds);
	draw_floor(img, &ds, cub->scene.colors.floor_color);
}
