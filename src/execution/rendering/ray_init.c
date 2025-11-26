/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:08:18 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static void	init_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

static void	init_step_x(t_cub3d *cub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->scene.player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->scene.player.pos_x)
			* ray->delta_dist_x;
	}
}

static void	init_step_y(t_cub3d *cub, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->scene.player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->scene.player.pos_y)
			* ray->delta_dist_y;
	}
}

void	compute_ray(t_cub3d *cub, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)cub->scene.screen_width - 1;
	ray->ray_dir_x = cub->scene.player.dir_x + cub->scene.player.plane_x
		* camera_x;
	ray->ray_dir_y = cub->scene.player.dir_y + cub->scene.player.plane_y
		* camera_x;
	ray->map_x = (int)cub->scene.player.pos_x;
	ray->map_y = (int)cub->scene.player.pos_y;
	init_delta_dist(ray);
	init_step_x(cub, ray);
	init_step_y(cub, ray);
	ray->hit = 0;
	ray->side = 0;
}
