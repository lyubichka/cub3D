/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:16:29 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 02:24:36 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

int	save_mode_render_and_write(t_scene *scene, const char *out_filename)
{
	t_cub3d	cub;
	int		res;

	if (!scene || !out_filename)
		return (-1);
	res = prepare_offscreen_cub(&cub, scene);
	if (res != 0)
		return (-1);
	if (create_offscreen_image(&cub) != 0)
	{
		if (cub.img.img)
			mlx_destroy_image(cub.mlx, cub.img.img);
		return (-1);
	}
	render_scene(&cub);
	res = save_bmp_file(&cub.img, cub.scene.screen_width,
			cub.scene.screen_height, out_filename);
	cleanup_offscreen(&cub);
	if (res == 0)
		return (0);
	return (-1);
}
