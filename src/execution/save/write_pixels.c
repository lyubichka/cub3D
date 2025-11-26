/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:19:00 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static int	write_pixel_row(FILE *f, t_bmp_write *bmp, int row)
{
	unsigned char	pixel_buf[3];
	unsigned char	rgb[3];
	uint32_t		pixel;
	int				col;

	col = 0;
	while (col < bmp->width)
	{
		pixel = build_pixel(bmp->addr + row * bmp->line_len
				+ col * bmp->bpp_bytes, bmp->bpp_bytes);
		extract_rgb(pixel, rgb);
		pixel_buf[0] = rgb[0];
		pixel_buf[1] = rgb[1];
		pixel_buf[2] = rgb[2];
		if (fwrite(pixel_buf, 1, 3, f) != 3)
			return (-1);
		col++;
	}
	return (write_row_padding(f, bmp->pad_len));
}

static void	init_bmp_write(t_bmp_write *bmp, t_image *img, int width)
{
	bmp->addr = (unsigned char *)img->addr;
	bmp->line_len = img->line_len;
	bmp->bpp_bytes = img->bpp / 8;
	if (bmp->bpp_bytes <= 0)
		bmp->bpp_bytes = 4;
	bmp->width = width;
	bmp->pad_len = (4 - ((width * 3) % 4)) % 4;
}

int	write_pixel_data(FILE *f, t_image *img, int width, int height)
{
	t_bmp_write	bmp;
	int			row;

	init_bmp_write(&bmp, img, width);
	if (!bmp.addr)
		return (-1);
	row = height - 1;
	while (row >= 0)
	{
		if (write_pixel_row(f, &bmp, row) != 0)
			return (-1);
		row--;
	}
	return (0);
}
