/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 02:42:25 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 16:32:52 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
    if (!game)
        return;
    destroy_images(game);
    destroy_window(game);
    free_textures(game);
    free_map_grid(game);
    free_map_cols(game);
}

void	exit_game(t_game *game, char *msg, int code)
{
    if (msg)
        ft_putendl_fd(msg, 2);
    if (game)
        free_game(game);
    exit(code);
}