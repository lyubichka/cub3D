/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:08:15 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static void	step_ray_x(t_ray *ray)
{
	ray->side_dist_x += ray->delta_dist_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

static void	step_ray_y(t_ray *ray)
{
	ray->side_dist_y += ray->delta_dist_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
}

void	perform_dda(t_cub3d *cub, t_ray *ray)
{
	int	map_w;
	int	map_h;

	map_w = cub->scene.map.width;
	map_h = cub->scene.map.height;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			step_ray_x(ray);
		else
			step_ray_y(ray);
		if (ray->map_x < 0 || ray->map_x >= map_w || ray->map_y < 0
			|| ray->map_y >= map_h)
		{
			ray->hit = 1;
			break ;
		}
		if (cub->scene.map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
