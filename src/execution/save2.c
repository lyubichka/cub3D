/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:16:29 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 20:32:59 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* prepare a minimal cub for offscreen render: copy scene, init mlx and player */
static int prepare_offscreen_cub(t_cub3d *cub, t_scene *scene)
{
	cub->scene = *scene;
	cub->keys.w = cub->keys.a = cub->keys.s = cub->keys.d = 0;
	cub->keys.left = cub->keys.right = cub->keys.escape = 0;
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		fprintf(stderr, "Error: mlx_init failed\n");
		return (-1);
	}
	cub->win = NULL; /* no window for save mode */
	init_player(&cub->scene);
	return (0);
}

/* create offscreen image into cub->img */
static int create_offscreen_image(t_cub3d *cub)
{
	init_image(cub->mlx, &cub->img, cub->scene.screen_width, cub->scene.screen_height);
	if (!cub->img.img || !cub->img.addr)
	{
		fprintf(stderr, "Error: failed to create offscreen image\n");
		return (-1);
	}
	return (0);
}

/* cleanup offscreen image and mlx references */
static void cleanup_offscreen(t_cub3d *cub)
{
	if (cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	/* Some MLX implementations may require additional cleanup; skip exit here */
}

/* render one frame into offscreen image and write BMP */
int save_mode_render_and_write(t_scene *scene, const char *out_filename)
{
	t_cub3d cub;
	int res;

	if (!scene || !out_filename)
		return (-1);
	res = prepare_offscreen_cub(&cub, scene);
	if (res != 0)
		return (-1);
	if (create_offscreen_image(&cub) != 0)
	{
		/* attempt cleanup */
		if (cub.img.img) mlx_destroy_image(cub.mlx, cub.img.img);
		return (-1);
	}

	/* render into cub.img (render_scene must avoid window call when cub.win==NULL) */
	render_scene(&cub);

	/* write BMP */
	res = save_bmp_file(&cub.img, cub.scene.screen_width, cub.scene.screen_height, out_filename);

	/* cleanup and return */
	cleanup_offscreen(&cub);
	return (res == 0 ? 0 : -1);
}

