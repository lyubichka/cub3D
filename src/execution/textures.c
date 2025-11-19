/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:21:49 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 14:22:04 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	load_single_texture(t_cub3d *cub, t_image *tex, const char *path)
{
	void *img;
	int w;
	int h;

	img = mlx_xpm_file_to_image(cub->mlx, (char *)path, &w, &h);
	if (!img)
		print_error("Failed to load texture XPM");

	tex->img = img;
	tex->addr = mlx_get_data_addr(img, &tex->bpp, &tex->line_len, &tex->endian);
	tex->width = w;
	tex->height = h;
}

/* call this after cub->mlx is initialized and before the render loop */
void load_textures(t_cub3d *cub)
{
	/* paths come from parsed scene */
	load_single_texture(cub, &cub->textures[TEX_NORTH], cub->scene.textures.north);
	load_single_texture(cub, &cub->textures[TEX_SOUTH], cub->scene.textures.south);
	load_single_texture(cub, &cub->textures[TEX_EAST],  cub->scene.textures.east);
	load_single_texture(cub, &cub->textures[TEX_WEST],  cub->scene.textures.west);
}

/* free texture images (call on close) */
void free_textures(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (cub->textures[i].img)
			mlx_destroy_image(cub->mlx, cub->textures[i].img);
		i++;
	}
}

