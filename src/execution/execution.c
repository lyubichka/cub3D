/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:27:18 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/24 14:06:26 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void run_engine(t_scene *scene)
{
	t_cub3d *cub;

	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		print_error("malloc failed");

	/* copy scene into cub->scene (or assign pointer if you prefer) */
	cub->scene = *scene;
	free(scene); /* free original scene if copied */
	ft_bzero(&cub->keys, sizeof(t_keys)); /* clear key state */

	/* initialize MLX, window and the persistent image */
	init_graphics(cub);

	/* register hooks */
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, handle_close, cub);
	mlx_loop_hook(cub->mlx, frame_loop, cub);

	/* enter loop */
	mlx_loop(cub->mlx);

	/* function will not reach here typically; cleanup done in handle_close */
}

/* this is called by mlx_loop_hook repeatedly */
int frame_loop(void *param)
{
	t_cub3d *cub = (t_cub3d *)param;

	handle_keys(cub);        /* update position/rotation from key states */
	render_scene(cub);       /* draw one frame */

	return (0);
}

void render_scene(t_cub3d *cub)
{
	t_image	*img;
	int		x;
	int		screen_w;
	int		screen_h;

	/* use persistent image from cub */
	img = &cub->img;
	screen_w = cub->scene.screen_width;
	screen_h = cub->scene.screen_height;

	/* clear image buffer once per frame (fast) */
	ft_bzero(img->addr, img->line_len * screen_h);

	x = 0;
	while (x < screen_w)
	{
		t_ray ray;

		/* compute_ray expects cub and x and fills ray */
		ft_bzero(&ray, sizeof(t_ray));
		/* compute_ray uses cameraX = 2 * x / screen_w - 1, we precomputed inv_width above */
		/* but keep compute_ray as-is; or pass inv_width if you modified it */
		compute_ray(cub, x, &ray);

		perform_dda(cub, &ray);
		compute_wall_height(cub, &ray);
		draw_vertical_stripe_textured(&cub->img, cub, x, &ray);

		x++;
	}
	draw_minimap(cub, &cub->img);
	/* draw the persistent image to the window; do NOT destroy the image */
	if (cub->win)
    mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
