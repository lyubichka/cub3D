/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:27:18 by haiqbal           #+#    #+#             */
/*   Updated: 2026/01/11 19:48:14 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	run_engine(t_scene *scene)
{
	t_cub3d	*cub;

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
	{
		free_full_scene(scene);
		print_error_ctx("run_engine: malloc failed", NULL, NULL);
	}
	cub->scene = *scene;
	free(scene);
	ft_bzero(&cub->keys, sizeof(t_keys));
	init_player(&cub->scene);
	init_graphics(cub);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, handle_close, cub);
	mlx_loop_hook(cub->mlx, frame_loop, cub);
	mlx_loop(cub->mlx);
}

int	frame_loop(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	handle_keys(cub);
	render_scene(cub);
	return (0);
}

void	render_scene(t_cub3d *cub)
{
	t_image	*img;
	int		x;
	int		screen_w;
	int		screen_h;
	t_ray	ray;

	img = &cub->img;
	screen_w = cub->scene.screen_width;
	screen_h = cub->scene.screen_height;
	ft_bzero(img->addr, img->line_len * screen_h);
	x = 0;
	while (x < screen_w)
	{
		ft_bzero(&ray, sizeof(t_ray));
		compute_ray(cub, x, &ray);
		perform_dda(cub, &ray);
		compute_wall_height(cub, &ray);
		draw_vertical_stripe_textured(&cub->img, cub, x, &ray);
		x++;
	}
	draw_minimap(cub, &cub->img);
	if (cub->win)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
