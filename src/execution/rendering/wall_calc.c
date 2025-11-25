/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:08:25 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static double	calc_perp_dist_x(t_cub3d *cub, t_ray *ray)
{
	double	perp_dist;

	if (ray->ray_dir_x == 0.0)
		perp_dist = 1e30;
	else
		perp_dist = (ray->map_x - cub->scene.player.pos_x + (1 - ray->step_x)
				/ 2.0) / ray->ray_dir_x;
	return (perp_dist);
}

static double	calc_perp_dist_y(t_cub3d *cub, t_ray *ray)
{
	double	perp_dist;

	if (ray->ray_dir_y == 0.0)
		perp_dist = 1e30;
	else
		perp_dist = (ray->map_y - cub->scene.player.pos_y + (1 - ray->step_y)
				/ 2.0) / ray->ray_dir_y;
	return (perp_dist);
}

static double	calc_perp_dist(t_cub3d *cub, t_ray *ray)
{
	double	perp_dist;

	if (ray->hit == 0)
		perp_dist = 1e30;
	else if (ray->side == 0)
		perp_dist = calc_perp_dist_x(cub, ray);
	else
		perp_dist = calc_perp_dist_y(cub, ray);
	if (perp_dist <= 0.0)
		perp_dist = 1e-6;
	return (perp_dist);
}

void	compute_wall_height(t_cub3d *cub, t_ray *ray)
{
	double	perp_dist;
	int		screen_h;

	screen_h = cub->scene.screen_height;
	perp_dist = calc_perp_dist(cub, ray);
	ray->perp_wall_dist = perp_dist;
	ray->line_height = (int)((double)screen_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screen_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_h / 2;
	if (ray->draw_end >= screen_h)
		ray->draw_end = screen_h - 1;
}
