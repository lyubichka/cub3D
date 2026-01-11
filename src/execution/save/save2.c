/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:16:29 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/11 19:59:58 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static int	handle_image_creation(t_cub3d *cub)
{
	if (create_offscreen_image(cub) != 0)
	{
		if (cub->img.img)
			mlx_destroy_image(cub->mlx, cub->img.img);
		cleanup_offscreen(cub);
		return (-1);
	}
	return (0);
}

static int	render_and_save(t_cub3d *cub, const char *out_filename)
{
	int	res;

	render_scene(cub);
	res = save_bmp_file(&cub->img, cub->scene.screen_width,
			cub->scene.screen_height, out_filename);
	cleanup_offscreen(cub);
	if (res == 0)
		return (0);
	return (-1);
}

int	save_mode_render_and_write(t_scene *scene, const char *out_filename)
{
	t_cub3d	cub;
	int		res;

	if (!scene || !out_filename)
		return (-1);
	res = prepare_offscreen_cub(&cub, scene);
	if (res != 0)
	{
		if (cub.mlx)
		{
			mlx_destroy_display(cub.mlx);
			free(cub.mlx);
		}
		return (-1);
	}
	if (handle_image_creation(&cub) != 0)
		return (-1);
	return (render_and_save(&cub, out_filename));
}
