/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:08:22 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

int	get_texture_index(t_ray *ray)
{
	int	tex_idx;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			tex_idx = TEX_WEST;
		else
			tex_idx = TEX_EAST;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			tex_idx = TEX_NORTH;
		else
			tex_idx = TEX_SOUTH;
	}
	return (tex_idx);
}

double	calc_wall_x(t_cub3d *cub, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub->scene.player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = cub->scene.player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calc_tex_x(double wall_x, t_image *tex, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	init_texture_params(t_cub3d *cub, t_ray *ray, t_tex_params *params)
{
	params->step = 1.0 * params->tex->height / (double)ray->line_height;
	params->tex_pos = (ray->draw_start - cub->scene.screen_height / 2
			+ ray->line_height / 2) * params->step;
}
