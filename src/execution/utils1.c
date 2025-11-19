/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:40:16 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 14:25:36 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int handle_close(void *param)
{
	t_cub3d *cub;

	if (!param)
		exit(0);
	cub = (t_cub3d *)param;

	free_textures(cub);

	/* destroy persistent image and window */
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);

	/* If you allocated textures or scene strings dynamically, free them here.
	   If cub->scene is a copy of parsed scene, ensure the original will be freed
	   or move to pointer-style ownership. For testing you can skip freeing those
	   until program exit. */

	free(cub);
	exit(0);

	return (0);
}


