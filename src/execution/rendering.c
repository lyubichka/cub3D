/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:30:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 01:44:37 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
	ray->side = 0;
}

void perform_dda(t_cub3d *cub, t_ray *ray)
{
	int map_w;
	int map_h;

	map_w = cub->scene.map.width;
	map_h = cub->scene.map.height;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0; /* vertical side hit */
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1; /* horizontal side hit */
		}
		if (ray->mapX < 0 || ray->mapX >= map_w ||
			ray->mapY < 0 || ray->mapY >= map_h)
		{
			ray->hit = 1;
			break;
		}
		if (cub->scene.map.grid[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void compute_wall_height(t_cub3d *cub, t_ray *ray)
{
	double perpDist;
	int screen_h;

	screen_h = cub->scene.screen_height;

	/* Compute perpendicular distance; guard against dividing by 0 */
	if (ray->hit == 0)
	{
		/* If DDA ended without a hit (shouldn't normally happen), set huge distance */
		perpDist = 1e30;
	}
	else if (ray->side == 0)
	{
		/* vertical side - use X-component */
		if (ray->rayDirX == 0.0)
			perpDist = 1e30;
		else
			perpDist = (ray->mapX - cub->scene.player.pos_x + (1 - ray->stepX) / 2.0) / ray->rayDirX;
	}
	else
	{
		/* horizontal side - use Y-component */
		if (ray->rayDirY == 0.0)
			perpDist = 1e30;
		else
			perpDist = (ray->mapY - cub->scene.player.pos_y + (1 - ray->stepY) / 2.0) / ray->rayDirY;
	}

	/* If perpDist is negative due to numeric issues, force positive */
	if (perpDist <= 0.0)
		perpDist = 1e-6;

	ray->perpWallDist = perpDist;

	/* projected line height (avoid divide by zero by ensuring perpDist > 0) */
	ray->lineHeight = (int)((double)screen_h / ray->perpWallDist);

	/* center vertically */
	ray->drawStart = -ray->lineHeight / 2 + screen_h / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;

	ray->drawEnd = ray->lineHeight / 2 + screen_h / 2;
	if (ray->drawEnd >= screen_h)
		ray->drawEnd = screen_h - 1;
}

void draw_vertical_stripe(t_image *img, t_cub3d *cub, int x, t_ray *ray)
{
	int y;
	int color;

	if (ray->side == 1)
		color = 0xAAAAAA;
	else
		color = 0xFFFFFF;

	/* draw ceiling until drawStart (if drawStart > 0) */
	y = 0;
	while (y < ray->drawStart)
	{
		put_pixel(img, x, y, cub->scene.colors.ceiling_color);
		y++;
	}

	/* draw wall slice only if there's something to draw */
	if (ray->drawStart <= ray->drawEnd)
	{
		y = ray->drawStart;
		while (y <= ray->drawEnd)
		{
			put_pixel(img, x, y, color);
			y++;
		}
	}

	/* draw floor below drawEnd */
	y = ray->drawEnd + 1;
	while (y < cub->scene.screen_height)
	{
		put_pixel(img, x, y, cub->scene.colors.floor_color);
		y++;
	}
}

