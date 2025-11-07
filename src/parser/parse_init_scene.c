/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronikalubickaa <veronikalubickaa@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:19:10 by veronikalub       #+#    #+#             */
/*   Updated: 2025/11/06 19:20:34 by veronikalub      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void init_scene_defaults(t_scene *scene)
{
    scene->screen_width = 0;
    scene->screen_height = 0;
    scene->textures.north = NULL;
    scene->textures.south = NULL;
    scene->textures.west = NULL;
    scene->textures.east = NULL;
    scene->textures.sprite = NULL;
    scene->colors.floor[0] = 0;
    scene->colors.floor[1] = 0;
    scene->colors.floor[2] = 0;
    scene->colors.ceiling[0] = 0;
    scene->colors.ceiling[1] = 0;
    scene->colors.ceiling[2] = 0;
    scene->colors.floor_color = -1;
    scene->colors.ceiling_color = -1;
    scene->map.grid = NULL;
    scene->map.width = 0;
    scene->map.height = 0;
    scene->map.player_x = 0;
    scene->map.player_y = 0;
    scene->map.player_dir = 'N';
}

static t_scene *alloc_init_scene(bool save_flag)
{
    t_scene *scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
    if (!scene)
        print_error("Error: Memory allocation failed for t_scene");
    scene->save_bmp = save_flag ? 1 : 0;
    init_scene_defaults(scene);
    return (scene);
}