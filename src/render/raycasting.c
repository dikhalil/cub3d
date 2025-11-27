/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:28:59 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 22:58:31 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_game *game)
{
    t_ray	ray;
    t_wall	wall;
    int		x;

    x = 0;
    while (x < WIDTH)
    {
        init_ray(&ray, game, x);
        set_step_and_side_dist(&ray, game);
        perform_dda(&ray, game);
        calculate_wall_distance(&ray);
        init_wall_data(&wall, &ray, game);
        select_texture(&wall, &ray);
        calculate_texture_x(&wall, game);
        draw_vertical_line(game, x, &wall);
        x++;
    }
}
