/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:41:14 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 14:28:12 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*
** Initializes an image buffer that you can draw into.
** You’ll call this before starting to render each frame.
*/
void	init_image(void *mlx, t_image *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

/*
** Draws a pixel at position (x, y) with a given color (0xRRGGBB).
** This writes directly into the image’s memory buffer.
*/
void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* read a pixel (tx,ty) from texture `tex` and return 0xRRGGBB int */
int get_tex_color(t_image *tex, int tx, int ty)
{
	char *pixel;
	unsigned int color;

	/* clamp tx/ty just in case */
	if (tx < 0)
		tx = 0;
	if (tx >= tex->width)
		tx = tex->width - 1;
	if (ty < 0)
		ty = 0;
	if (ty >= tex->height)
		ty = tex->height - 1;

	pixel = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	color = *(unsigned int *)pixel;
	return ((int)color);
}


