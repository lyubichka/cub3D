/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:27:18 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/18 16:46:41 by haiqbal          ###   ########.fr       */
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

void 	render_scene(t_cub3d *cub)
{
	t_image img;
	int x;
	t_ray ray;

	init_image(cub->mlx, &img,
		cub->scene.screen_width,
		cub->scene.screen_height);

	x = 0;
	while (x < cub->scene.screen_width)
	{
		ft_bzero(&ray, sizeof(t_ray));
		compute_ray(cub, x, &ray);
		perform_dda(cub, &ray);
		compute_wall_height(cub, &ray);
		draw_vertical_stripe(&img, cub, x, &ray);
		x++;
	}

	mlx_put_image_to_window(cub->mlx, cub->win, img.img, 0, 0);
}
