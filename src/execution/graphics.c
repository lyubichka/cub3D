/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 01:57:58 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/26 00:34:22 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void init_graphics(t_cub3d *cub)
{
    if (!cub)
        print_error("init_graphics: null cub");
    cub->mlx = mlx_init();
    if (!cub->mlx)
        print_error("mlx_init failed");
    cub->win = mlx_new_window(cub->mlx,
            cub->scene.screen_width,
            cub->scene.screen_height,
            "cub3D");
    if (!cub->win)
        print_error("mlx_new_window failed");
    init_image(cub->mlx, &cub->img,
        cub->scene.screen_width,
        cub->scene.screen_height);
    ft_bzero(cub->img.addr, cub->img.line_len * cub->scene.screen_height);
    load_textures(cub);
}




