/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:19:00 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

uint32_t	build_pixel(unsigned char *p, int bpp_bytes)
{
	uint32_t	pixel;
	int			k;

	pixel = 0;
	k = 0;
	while (k < bpp_bytes && k < 4)
	{
		pixel |= ((uint32_t)p[k]) << (8 * k);
		k++;
	}
	return (pixel);
}

void	extract_rgb(uint32_t pixel, unsigned char *buf)
{
	buf[0] = (unsigned char)(pixel & 0xFF);
	buf[1] = (unsigned char)((pixel >> 8) & 0xFF);
	buf[2] = (unsigned char)((pixel >> 16) & 0xFF);
}

int	write_row_padding(FILE *f, int pad_len)
{
	unsigned char	pad[3];

	pad[0] = 0;
	pad[1] = 0;
	pad[2] = 0;
	if (pad_len && fwrite(pad, 1, pad_len, f) != (size_t)pad_len)
		return (-1);
	return (0);
}
