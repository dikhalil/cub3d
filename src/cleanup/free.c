/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:31:09 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 22:54:46 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(t_game *game)
{
	int	i;

	if (!game || !game->mlx.ctx)
		return ;
	i = 0;
	while (i < 5)
	{
		if (game->mlx.imgs[i].img)
		{
			mlx_destroy_image(game->mlx.ctx, game->mlx.imgs[i].img);
			game->mlx.imgs[i].img = NULL;
		}
		i++;
	}
}

void	destroy_window(t_game *game)
{
	if (!game || !game->mlx.ctx)
		return ;
	if (game->mlx.win)
	{
		mlx_destroy_window(game->mlx.ctx, game->mlx.win);
		game->mlx.win = NULL;
	}
	if (game->mlx.ctx)
	{
		mlx_destroy_display(game->mlx.ctx);
		free(game->mlx.ctx);
		game->mlx.ctx = NULL;
	}
}

void	free_map_grid(t_game *game)
{
	int	i;

	if (!game || !game->map.grid)
		return ;
	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.grid[i])
			free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

void	free_map_cols(t_game *game)
{
	if (!game || !game->map.cols)
		return ;
	free(game->map.cols);
	game->map.cols = NULL;
}

void	free_textures(t_game *game)
{
	if (!game)
		return ;
	if (game->textures.north_path)
	{
		free(game->textures.north_path);
		game->textures.north_path = NULL;
	}
	if (game->textures.south_path)
	{
		free(game->textures.south_path);
		game->textures.south_path = NULL;
	}
	if (game->textures.west_path)
	{
		free(game->textures.west_path);
		game->textures.west_path = NULL;
	}
	if (game->textures.east_path)
	{
		free(game->textures.east_path);
		game->textures.east_path = NULL;
	}
}
