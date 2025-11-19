/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 01:57:58 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 02:00:51 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* init_image is your helper that calls mlx_new_image + mlx_get_data_addr */
void init_graphics(t_cub3d *cub)
{
	if (!cub)
		return ;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		print_error("mlx_init failed");

	cub->win = mlx_new_window(cub->mlx,
			cub->scene.screen_width,
			cub->scene.screen_height,
			"cub3D");
	if (!cub->win)
		print_error("mlx_new_window failed");

	/* create the persistent image once and cache addr/bpp/line_len/endian */
	init_image(cub->mlx, &cub->img,
		cub->scene.screen_width,
		cub->scene.screen_height);

	/* clear initial buffer */
	ft_bzero(cub->img.addr, cub->img.line_len * cub->scene.screen_height);
}



