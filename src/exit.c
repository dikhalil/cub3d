/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:13:36 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/26 01:39:49 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_mlx(t_mlx *mlx)
{
    int i;

    i = 0;
    if (!mlx)
        return ;
    if (mlx->ctx)
    {
        while (i < 4)
        {
            if (mlx->imgs[i].img)
                mlx_destroy_image(mlx->ctx, mlx->imgs[i].img);
            i++;
        }
        if (mlx->win)
            mlx_destroy_window(mlx->ctx, mlx->win);
        mlx_destroy_display(mlx->ctx);
		free(mlx->ctx);
    }
}

static void free_map(t_map *map)
{
    int i;

    i = 0;
    if (!map)
        return ;
    if (map->grid)
    {
        while (map->grid[i])
            free(map->grid[i++]);
        free(map->grid);
        map->grid = NULL;
    }
    if (map->cols)
    {
        free(map->cols);
        map->cols = NULL;
    }
}

static void free_textures(t_textures *textures)
{
    if (!textures)
        return ;
    if (textures->north_path)
        free(textures->north_path);
    if (textures->south_path)
        free(textures->south_path);
    if (textures->west_path)
        free(textures->west_path);
    if (textures->east_path)
        free(textures->east_path);
}

void free_game(t_game *game)
{
    if (!game)
        return ;
    free_map(&game->map);
    free_textures(&game->textures);
    free_mlx(&game->mlx);
}

void exit_game(t_game *game, char *msg, int status)
{
    free_game(game);
    if (msg)
        ft_putendl_fd(msg, status);
    exit(status);
}