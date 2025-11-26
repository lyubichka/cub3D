/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:19:00 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

int	write_file_header(FILE *f, uint32_t file_size, uint32_t pixel_offset)
{
	unsigned char	header[14];

	header[0] = 'B';
	header[1] = 'M';
	header[2] = (unsigned char)(file_size & 0xFF);
	header[3] = (unsigned char)((file_size >> 8) & 0xFF);
	header[4] = (unsigned char)((file_size >> 16) & 0xFF);
	header[5] = (unsigned char)((file_size >> 24) & 0xFF);
	header[6] = 0;
	header[7] = 0;
	header[8] = 0;
	header[9] = 0;
	header[10] = (unsigned char)(pixel_offset & 0xFF);
	header[11] = (unsigned char)((pixel_offset >> 8) & 0xFF);
	header[12] = (unsigned char)((pixel_offset >> 16) & 0xFF);
	header[13] = (unsigned char)((pixel_offset >> 24) & 0xFF);
	if (fwrite(header, 1, 14, f) != 14)
		return (-1);
	return (0);
}

static void	init_dib_array(unsigned char *dib)
{
	int	i;

	i = 0;
	while (i < 40)
	{
		dib[i] = 0;
		i++;
	}
}

int	write_dib_header(FILE *f, int width, int height)
{
	unsigned char	dib[40];

	init_dib_array(dib);
	dib[0] = 40;
	dib[4] = (unsigned char)(width & 0xFF);
	dib[5] = (unsigned char)((width >> 8) & 0xFF);
	dib[6] = (unsigned char)((width >> 16) & 0xFF);
	dib[7] = (unsigned char)((width >> 24) & 0xFF);
	dib[8] = (unsigned char)(height & 0xFF);
	dib[9] = (unsigned char)((height >> 8) & 0xFF);
	dib[10] = (unsigned char)((height >> 16) & 0xFF);
	dib[11] = (unsigned char)((height >> 24) & 0xFF);
	dib[12] = 1;
	dib[14] = 24;
	if (fwrite(dib, 1, 40, f) != 40)
		return (-1);
	return (0);
}
