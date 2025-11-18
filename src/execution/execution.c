/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:27:18 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 00:48:16 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void run_engine(t_scene *scene)
{
	t_cub3d *cub;

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		print_error("malloc failed");
	/* copy parsed scene into engine struct */
	cub->scene = *scene;
	ft_memset(&cub->keys, 0, sizeof(t_keys)); /* or assign zeros manually */
	cub->mlx = mlx_init();
	if (!cub->mlx)
		print_error("mlx_init failed");
	cub->win = mlx_new_window(cub->mlx,
			cub->scene.screen_width,
			cub->scene.screen_height,
			"cub3D");
	if (!cub->win)
		print_error("mlx_new_window failed");
	init_player(&cub->scene);
	/* register event hooks */
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, handle_close, cub);
	mlx_loop_hook(cub->mlx, frame_loop, cub);
	mlx_loop(cub->mlx);
	/* control won't reach here; cleanup should be done in close handler */
}

/* this is called by mlx_loop_hook repeatedly */
int frame_loop(void *param)
{
	t_cub3d *cub = (t_cub3d *)param;

	handle_keys(cub);        /* update position/rotation from key states */
	render_scene(cub);       /* draw one frame */

	return (0);
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
	mlx_destroy_image(cub->mlx, img.img);
}
