/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:40:16 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/23 17:09:50 by veronikalub      ###   ########.fr       */
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

	/* destroy persistent image and window */
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	exit(0);

	return (0);
}


