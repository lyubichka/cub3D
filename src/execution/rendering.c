/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:30:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 15:39:01 by haiqbal          ###   ########.fr       */
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
/*
 * draw_vertical_stripe_textured:
 * - img : frame buffer
 * - cub : engine + textures
 * - x   : column on screen
 * - ray : ray data including drawStart/drawEnd/lineHeight/perpWallDist
 */
void draw_vertical_stripe_textured(t_image *img, t_cub3d *cub, int x, t_ray *ray)
{
	t_image *tex;
	int		y;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
	int		color;
	int		texIdx;

	/* choose texture based on side of wall and map orientation:
	   for simplicity: if side==0 (vertical wall) pick east/west depending on rayDirX sign.
	   if side==1 (horizontal) pick north/south depending on rayDirY sign.
	*/
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			texIdx = TEX_WEST;  /* looking to +X hits west face */
		else
			texIdx = TEX_EAST;
	}
	else
	{
		if (ray->rayDirY > 0)
			texIdx = TEX_NORTH; /* looking to +Y hits north face */
		else
			texIdx = TEX_SOUTH;
	}
	tex = &cub->textures[texIdx];

	/* Calculate the exact position where the wall was hit (wallX),
	   this is used to pick correct texture column.
	   If side == 0, wall was hit at some y coordinate; else at some x.
	*/
	if (ray->side == 0)
		wallX = cub->scene.player.pos_y + ray->perpWallDist * ray->rayDirY;
	else
		wallX = cub->scene.player.pos_x + ray->perpWallDist * ray->rayDirX;
	wallX -= floor(wallX); /* keep fractional part only [0..1) */

	/* texX is the texture x-coordinate */
	texX = (int)(wallX * (double)tex->width);
	/* flips when needed (so textures appear not mirrored) */
	if (ray->side == 0 && ray->rayDirX > 0)
		texX = tex->width - texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		texX = tex->width - texX - 1;

	/* Step size in texture space for each screen pixel */
	step = 1.0 * tex->height / (double)ray->lineHeight;

	/* starting texture y coordinate */
	texPos = (ray->drawStart - cub->scene.screen_height / 2 + ray->lineHeight / 2) * step;

	/* draw ceiling above */
	y = 0;
	while (y < ray->drawStart)
	{
		put_pixel(img, x, y, cub->scene.colors.ceiling_color);
		y++;
	}

	/* draw wall slice (texture sampled) */
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		int texY = (int)texPos & (tex->height - 1); /* faster mod if power of two; OK otherwise */
		/* get pixel from texture */
		color = get_tex_color(tex, texX, texY);

		/* shade if side==1 to simulate lighting (darker) */
		if (ray->side == 1)
			color = ((color >> 1) & 0x7F7F7F); /* simple half-brightness */

		put_pixel(img, x, y, color);
		texPos += step;
		y++;
	}

	/* draw floor below */
	y = ray->drawEnd + 1;
	while (y < cub->scene.screen_height)
	{
		put_pixel(img, x, y, cub->scene.colors.floor_color);
		y++;
	}
}


