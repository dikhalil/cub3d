/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:13:36 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/04 22:05:06 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_game(t_game *game)
{
    int i;

    i = 0;
    if (game->map.grid)
    {
        while (game->map.grid[i])
            free(game->map.grid[i++]);
        free(game->map.grid);
    }
    if (game->map.cols)
        free(game->map.cols);
}

void exit_game(t_game *game, char *msg, int status)
{
    if (game)
        free_game(game);
    if (msg)
        printf("%s\n",msg);
    exit(status);
}