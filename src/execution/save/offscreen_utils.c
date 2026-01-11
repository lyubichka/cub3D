/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offscreen_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:00:00 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/11 14:37:39 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->escape = 0;
}

int	prepare_offscreen_cub(t_cub3d *cub, t_scene *scene)
{
	cub->scene = *scene;
	init_keys(&cub->keys);
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		fprintf(stderr, "Error: mlx_init failed\n");
		return (-1);
	}
	cub->win = NULL;
	load_textures(cub);
	init_player(&cub->scene);
	return (0);
}

int	create_offscreen_image(t_cub3d *cub)
{
	init_image(cub->mlx, &cub->img, cub->scene.screen_width,
		cub->scene.screen_height);
	if (!cub->img.img || !cub->img.addr)
	{
		fprintf(stderr, "Error: failed to create offscreen image\n");
		return (-1);
	}
	return (0);
}

void	cleanup_offscreen(t_cub3d *cub)
{
	free_textures(cub);
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}
