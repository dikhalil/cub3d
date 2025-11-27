/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:30:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 16:37:54 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_vector(double *x, double *y, double angle)
{
    double	old_x;

    old_x = *x;
    *x = *x * cos(angle) - *y * sin(angle);
    *y = old_x * sin(angle) + *y * cos(angle);
}

void	rotate_left(t_game *game)
{
    rotate_vector(&game->player.dir_x, &game->player.dir_y, ROT_SPEED);
    rotate_vector(&game->player.plane_x, &game->player.plane_y, ROT_SPEED);
}

void	rotate_right(t_game *game)
{
    rotate_vector(&game->player.dir_x, &game->player.dir_y, -ROT_SPEED);
    rotate_vector(&game->player.plane_x, &game->player.plane_y, -ROT_SPEED);
}

void	rotate_mouse(t_game *game, double angle)
{
    rotate_vector(&game->player.dir_x, &game->player.dir_y, angle);
    rotate_vector(&game->player.plane_x, &game->player.plane_y, angle);
}