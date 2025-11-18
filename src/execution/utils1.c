/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:40:16 by haiqbal           #+#    #+#             */
/*   Updated: 2025/11/19 00:40:30 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int handle_close(void *param)
{
	t_cub3d *cub = (t_cub3d *)param;

	mlx_destroy_window(cub->mlx, cub->win);
	free(cub);
	exit(0);
	return (0);
}

