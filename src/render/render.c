/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:01:19 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 17:06:29 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_game *game)
{
    game->mlx.ctx = mlx_init();
    if (!game->mlx.ctx)
        exit_game(game, "Error\nFailed to initialize MLX", 1);
    load_textures(game);
    game->mlx.win = mlx_new_window(game->mlx.ctx, WIDTH, HEIGHT, "Cub3D");
    if (!game->mlx.win)
        exit_game(game, "Error\nFailed to create window", 1);
    
    game->keys.w = 0;
    game->keys.s = 0;
    game->keys.a = 0;
    game->keys.d = 0;
    game->keys.left = 0;
    game->keys.right = 0;
    
    draw_game(game);
    mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
    mlx_hook(game->mlx.win, 3, 1L << 1, key_release, game);
    mlx_hook(game->mlx.win, 17, 0, close_window, game);
    mlx_hook(game->mlx.win, 6, 1L << 6, mouse_move, game);
    mlx_loop_hook(game->mlx.ctx, game_loop, game);
    mlx_loop(game->mlx.ctx);
}