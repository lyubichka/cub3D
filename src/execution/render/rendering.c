/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:30:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/18 16:46:49 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void compute_ray(t_cub3d *cub, int x, t_ray *ray)
{
	double cameraX;
	
	cameraX = 2 * x / (double)cub->scene.screen_width - 1;
	ray->rayDirX = cub->scene.player.dir_x + cub->scene.player.plane_x * cameraX;
	ray->rayDirY = cub->scene.player.dir_y + cub->scene.player.plane_y * cameraX;
	ray->mapX = (int)cub->scene.player.pos_x;
	ray->mapY = (int)cub->scene.player.pos_y;
	if (ray->rayDirX == 0.0)
	ray->deltaDistX = 1e30; /* effectively infinite */
	else
	ray->deltaDistX = fabs(1.0 / ray->rayDirX);
	if (ray->rayDirY == 0.0)
	ray->deltaDistY = 1e30;
	else
	ray->deltaDistY = fabs(1.0 / ray->rayDirY);
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (cub->scene.player.pos_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - cub->scene.player.pos_x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (cub->scene.player.pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - cub->scene.player.pos_y) * ray->deltaDistY;
	}
	ray->hit = 0;
}

void perform_dda(t_cub3d *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0; // vertical wall
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1; // horizontal wall
		}

		if (cub->scene.map.grid[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void compute_wall_height(t_cub3d *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayDirX != 0.0)
			ray->perpWallDist = (ray->mapX - cub->scene.player.pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
		else
			ray->perpWallDist = 1e30;
	}
	else
	{
		if (ray->rayDirY != 0.0)
			ray->perpWallDist = (ray->mapY - cub->scene.player.pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;
		else
			ray->perpWallDist = 1e30;
	}	
	ray->lineHeight = (int)(cub->scene.screen_height / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + cub->scene.screen_height / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + cub->scene.screen_height / 2;
	if (ray->drawEnd >= cub->scene.screen_height)
		ray->drawEnd = cub->scene.screen_height - 1;
}

void draw_vertical_stripe(t_image *img, t_cub3d *cub, int x, t_ray *ray)
{
	int y = 0;
	int color;

	if(ray->side == 1)
		color = 0xAAAAAA;
	else
		color = 0xFFFFFF;
	while (y < cub->scene.screen_height)
	{
		if (y < ray->drawStart)
			put_pixel(img, x, y, cub->scene.colors.ceiling_color);
		else if (y >= ray->drawStart && y <= ray->drawEnd)
			put_pixel(img, x, y, color);
		else
			put_pixel(img, x, y, cub->scene.colors.floor_color);
		y++;
	}
}
