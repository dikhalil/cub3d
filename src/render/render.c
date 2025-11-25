/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:01:19 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/25 23:51:15 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render(t_game *game)
{
    game->mlx.ctx = mlx_init();
    if (!game->mlx.ctx)
        exit_game(game, "Error\nFailed to initialize MLX", 1);
    load_textures(game);
    game->mlx.win = mlx_new_window(game->mlx.ctx, 800, 600, "Cub3D");
    if (!game->mlx.win)
        exit_game(game, "Error\nFailed to create window", 1); 
    draw_game(game);
    mlx_key_hook(game->mlx.win, key_hook, game);
    mlx_hook(game->mlx.win, 17, 0, close_window, game);
    mlx_loop(game->mlx.ctx);
}