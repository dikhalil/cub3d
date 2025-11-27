/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:50:42 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 22:12:15 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_textures(t_game *game)
{
    char *paths[4];
    int i;

    i = 0;
    paths[0] = game->textures.north_path;
    paths[1] = game->textures.south_path;
    paths[2] = game->textures.west_path;
    paths[3] = game->textures.east_path;
    while (i < 5)
    {
        if (i == 0)
        {
            game->mlx.imgs[0].img = mlx_new_image(game->mlx.ctx, 800, 600);
            game->mlx.imgs[0].width = 800;
            game->mlx.imgs[0].height = 600;
            if (!game->mlx.imgs[0].img)
                exit_game(game, "Error\nFailed to create screen buffer", 1);
        }
        else
        {
            game->mlx.imgs[i].img = mlx_xpm_file_to_image(game->mlx.ctx, paths[i - 1],
                &game->mlx.imgs[i].width, &game->mlx.imgs[i].height);
            if (!game->mlx.imgs[i].img)
            {
                ft_putstr_fd("Error\nInvalid XPM file: ", 2);
                ft_putendl_fd(paths[i - 1], 2);
                exit_game(game, NULL, 1);
            }
        }
        game->mlx.imgs[i].addr = mlx_get_data_addr(game->mlx.imgs[i].img,
                &game->mlx.imgs[i].bpp,
                &game->mlx.imgs[i].line_length,
                &game->mlx.imgs[i].endian);
        if (!game->mlx.imgs[i].addr)
            exit_game(game, "Error\nFailed to get texture data address", 1);
        i++;
    }
}

void draw_game(t_game *game)
{
    mlx_clear_window(game->mlx.ctx, game->mlx.win);
    cast_rays(game);
    mlx_put_image_to_window(game->mlx.ctx, game->mlx.win, 
            game->mlx.imgs[0].img, 0, 0);
}
