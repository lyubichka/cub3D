/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:19:00 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static uint32_t	calc_file_size(int width, int height)
{
	uint32_t	headers_size;
	int			row_size;
	int			pad_len;

	headers_size = 54;
	row_size = width * 3;
	pad_len = (4 - (row_size % 4)) % 4;
	return (headers_size + (row_size + pad_len) * (uint32_t)height);
}

static int	write_all_data(FILE *f, t_image *img, int width, int height)
{
	uint32_t	file_size;

	file_size = calc_file_size(width, height);
	if (write_file_header(f, file_size, 54) != 0)
		return (-1);
	if (write_dib_header(f, width, height) != 0)
		return (-1);
	if (write_pixel_data(f, img, width, height) != 0)
		return (-1);
	return (0);
}

int	save_bmp_file(t_image *img, int width, int height, const char *filename)
{
	FILE	*f;

	if (!img || !filename)
		return (-1);
	f = fopen(filename, "wb");
	if (!f)
		return (-1);
	if (write_all_data(f, img, width, height) != 0)
	{
		fclose(f);
		return (-1);
	}
	fclose(f);
	return (0);
}
