/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 01:57:58 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/11 19:49:42 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_graphics(t_cub3d *cub)
{
	if (!cub)
		print_error_ctx("init_graphics: null cub", NULL, NULL);
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		free_scene(&cub->scene);
		free(cub);
		print_error_ctx("mlx_init failed", NULL, NULL);
	}
	cub->win = mlx_new_window(cub->mlx, cub->scene.screen_width,
			cub->scene.screen_height, "cub3D");
	if (!cub->win)
	{
		free_scene(&cub->scene);
		free(cub);
		print_error_ctx("mlx_new_window failed", NULL, NULL);
	}
	init_image(cub->mlx, &cub->img, cub->scene.screen_width,
		cub->scene.screen_height);
	ft_bzero(cub->img.addr, cub->img.line_len * cub->scene.screen_height);
	load_textures(cub);
}
