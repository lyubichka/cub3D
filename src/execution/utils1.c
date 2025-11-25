/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:40:16 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/24 14:49:10 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int handle_close(void *param)
{
	t_cub3d *cub;

	if (!param)
		exit(0);
	cub = (t_cub3d *)param;

	/* free loaded texture images */
	free_textures(cub);
	free_scene(&cub->scene);
	/* destroy persistent image and window */
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	free(cub);
	exit(0);

	return (0);
}


