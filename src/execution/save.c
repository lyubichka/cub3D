/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:13:20 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 20:13:35 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* write 14-byte BMP file header */
static int write_file_header(FILE *f, uint32_t file_size, uint32_t pixel_offset)
{
	unsigned char header[14];

	/* signature 'BM' */
	header[0] = 'B'; header[1] = 'M';
	/* file size */
	header[2] = (unsigned char)(file_size & 0xFF);
	header[3] = (unsigned char)((file_size >> 8) & 0xFF);
	header[4] = (unsigned char)((file_size >> 16) & 0xFF);
	header[5] = (unsigned char)((file_size >> 24) & 0xFF);
	/* reserved 4 bytes */
	header[6] = header[7] = header[8] = header[9] = 0;
	/* pixel data offset */
	header[10] = (unsigned char)(pixel_offset & 0xFF);
	header[11] = (unsigned char)((pixel_offset >> 8) & 0xFF);
	header[12] = (unsigned char)((pixel_offset >> 16) & 0xFF);
	header[13] = (unsigned char)((pixel_offset >> 24) & 0xFF);

	if (fwrite(header, 1, 14, f) != 14)
		return (-1);
	return (0);
}

/* write 40-byte BITMAPINFOHEADER (DIB) */
static int write_dib_header(FILE *f, int width, int height)
{
	unsigned char dib[40];
	int i;

	i = 0;
	while (i < 40)
	{
		dib[i] = 0;
		i++;
	}

	/* header size */
	dib[0] = 40;
	/* width */
	dib[4] = (unsigned char)(width & 0xFF);
	dib[5] = (unsigned char)((width >> 8) & 0xFF);
	dib[6] = (unsigned char)((width >> 16) & 0xFF);
	dib[7] = (unsigned char)((width >> 24) & 0xFF);
	/* height */
	dib[8]  = (unsigned char)(height & 0xFF);
	dib[9]  = (unsigned char)((height >> 8) & 0xFF);
	dib[10] = (unsigned char)((height >> 16) & 0xFF);
	dib[11] = (unsigned char)((height >> 24) & 0xFF);
	/* planes = 1 */
	dib[12] = 1;
	/* bpp = 24 */
	dib[14] = 24;

	if (fwrite(dib, 1, 40, f) != 40)
		return (-1);
	return (0);
}

/* extract R,G,B from MLX pixel memory (little-endian bytes) */
static void extract_rgb_from_addr(unsigned char *p, int bpp_bytes,
	unsigned char *r, unsigned char *g, unsigned char *b)
{
	uint32_t pixel = 0;
	int k;

	k = 0;
	while (k < bpp_bytes && k < 4)
	{
		pixel |= ((uint32_t)p[k]) << (8 * k);
		k++;
	}
	/* common MLX layout: byte0 = B, byte1 = G, byte2 = R */
	*b = (unsigned char)(pixel & 0xFF);
	*g = (unsigned char)((pixel >> 8) & 0xFF);
	*r = (unsigned char)((pixel >> 16) & 0xFF);
}

/* write pixel data rows bottom-up with padding */
static int write_pixel_data(FILE *f, t_image *img, int width, int height)
{
	unsigned char pad[3] = {0,0,0};
	int pad_len;
	int row;
	int col;
	int line_len = img->line_len;
	int bpp_bytes = img->bpp / 8;
	unsigned char pixel_buf[3];
	unsigned char *addr;

	if (bpp_bytes <= 0)
		bpp_bytes = 4;
	addr = (unsigned char *)img->addr;
	if (!addr)
		return (-1);

	pad_len = (4 - ((width * 3) % 4)) % 4;

	row = height - 1;
	while (row >= 0)
	{
		col = 0;
		while (col < width)
		{
			unsigned char r, g, b;
			unsigned char *p = addr + row * line_len + col * bpp_bytes;
			extract_rgb_from_addr(p, bpp_bytes, &r, &g, &b);
			pixel_buf[0] = b;
			pixel_buf[1] = g;
			pixel_buf[2] = r;
			if (fwrite(pixel_buf, 1, 3, f) != 3)
				return (-1);
			col++;
		}
		if (pad_len)
		{
			if (fwrite(pad, 1, pad_len, f) != (size_t)pad_len)
				return (-1);
		}
		row--;
	}
	return (0);
}

/* public: save BMP file from t_image */
int save_bmp_file(t_image *img, int width, int height, const char *filename)
{
	FILE *f;
	uint32_t file_header_size = 14;
	uint32_t dib_header_size = 40;
	uint32_t headers_size = file_header_size + dib_header_size;
	int row_size_no_pad = width * 3;
	int pad_len = (4 - (row_size_no_pad % 4)) % 4;
	uint32_t pixel_data_size = (row_size_no_pad + pad_len) * (uint32_t)height;
	uint32_t file_size = headers_size + pixel_data_size;
	uint32_t pixel_offset = headers_size;

	if (!img || !filename)
		return (-1);
	f = fopen(filename, "wb");
	if (!f)
		return (-1);

	if (write_file_header(f, file_size, pixel_offset) != 0 ||
		write_dib_header(f, width, height) != 0 ||
		write_pixel_data(f, img, width, height) != 0)
	{
		fclose(f);
		return (-1);
	}
	fclose(f);
	return (0);
}

