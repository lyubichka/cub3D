/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:16:35 by veronikalub       #+#    #+#             */
/*   Updated: 2025/10/30 14:40:26 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int main(int argc, char **argv)
{
	t_scene *scene;
	bool save_flag = false;

	if (argc < 2 || argc > 3)
	{
		write(2, "Error\nwrong number of arguments\n", 33);
		exit(1);
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			save_flag = true;
		else
			print_error("Second argument must be '--save' if present");
	}
	scene = parse_scene(argv[1], save_flag);
	/* run_engine запустит графику: если save_flag==1 — сохранит bmp и выйдет */
	run_engine(scene);
 
	free_scene(scene);
	return (0);
}
