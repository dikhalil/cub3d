/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:02:58 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 22:14:32 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *line)
{
	int	i;

	i = 0;
	if (!line || !*line)
		return (0);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, "NO", 2) == 0
		|| ft_strncmp(line + i, "SO", 2) == 0
		|| ft_strncmp(line + i, "WE", 2) == 0
		|| ft_strncmp(line + i, "EA", 2) == 0)
		return (1);
	return (0);
}

static void	validate_texture_line(t_game *game, char *line, int *map_start)
{
	if (!line[0] || is_spaces(line))
		return ;
	if (is_texture(line))
	{
		set_texture_path(game, line);
		if (*map_start)
			exit_game(game, "Error\nTextures must be before map", 1);
	}
	else if (!is_color_chr(line) && is_map_chr(line[0]))
		*map_start = 1;
	else if (!is_color_chr(line))
		exit_game(game, "Error\nInvalid line in map", 1);
}

void	validate_textures(t_game *game)
{
	int		i;
	char	**line;
	int		map_start;

	i = 0;
	map_start = 0;
	line = game->map.grid;
	while (line[i])
	{
		validate_texture_line(game, line[i], &map_start);
		i++;
	}
	if (!game->textures.north_path || !game->textures.south_path
		|| !game->textures.west_path || !game->textures.east_path)
		exit_game(game, "Error\nEvery wall texture must be set once", 1);
}
