/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:27:18 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/11 20:03:22 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	run_engine(t_scene *scene)
{
	t_cub3d	cub;

	cub.scene = *scene;
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, scene->screen_width, scene->screen_height, "cub3D");
	init_player(&cub.scene);
	render_scene(&cub);
	mlx_loop(cub.mlx);
}