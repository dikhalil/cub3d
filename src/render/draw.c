/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:50:42 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/30 17:24:01 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_screen_buffer(t_game *game)
{
	game->mlx.imgs[0].img = mlx_new_image(game->mlx.ctx, WIDTH, HEIGHT);
	game->mlx.imgs[0].width = WIDTH;
	game->mlx.imgs[0].height = HEIGHT;
	if (!game->mlx.imgs[0].img)
		exit_game(game, "Error\nFailed to create screen buffer", 1);
	game->mlx.imgs[0].addr = mlx_get_data_addr(game->mlx.imgs[0].img,
			&game->mlx.imgs[0].bpp,
			&game->mlx.imgs[0].line_length,
			&game->mlx.imgs[0].endian);
	if (!game->mlx.imgs[0].addr)
		exit_game(game, "Error\nFailed to get texture data address", 1);
}

static void	load_xpm_texture(t_game *game, int i, char *path)
{
	game->mlx.imgs[i].img = mlx_xpm_file_to_image(game->mlx.ctx, path,
			&game->mlx.imgs[i].width, &game->mlx.imgs[i].height);
	if (!game->mlx.imgs[i].img)
	{
		ft_putstr_fd("Error\nInvalid XPM file: ", 2);
		ft_putendl_fd(path, 2);
		exit_game(game, NULL, 1);
	}
	game->mlx.imgs[i].addr = mlx_get_data_addr(game->mlx.imgs[i].img,
			&game->mlx.imgs[i].bpp,
			&game->mlx.imgs[i].line_length,
			&game->mlx.imgs[i].endian);
	if (!game->mlx.imgs[i].addr)
		exit_game(game, "Error\nFailed to get texture data address", 1);
}

void	load_textures(t_game *game)
{
	char	*paths[4];
	int		i;

	paths[0] = game->textures.north_path;
	paths[1] = game->textures.south_path;
	paths[2] = game->textures.west_path;
	paths[3] = game->textures.east_path;
	load_screen_buffer(game);
	i = 1;
	while (i < 5)
	{
		load_xpm_texture(game, i, paths[i - 1]);
		i++;
	}
}

void	draw_game(t_game *game)
{
	mlx_clear_window(game->mlx.ctx, game->mlx.win);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx.ctx, game->mlx.win, game->mlx.imgs[0].img,
		0, 0);
}
