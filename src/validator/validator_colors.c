/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:01:36 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/30 17:25:06 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_color_chr(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == 'F' || line[i] == 'C');
}

static t_color	*get_color(t_game *game, char *line)
{
	if (*line == 'F')
		return (&game->floor);
	return (&game->ceiling);
}

static void	set_color_value(t_game *game, char *line)
{
	t_color	*color;
	char	**rgb;
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	color = get_color(game, line + i);
	i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (count_commas(line + i) != 2)
		exit_game(game, "Error\nInvalid color format", 1);
	rgb = ft_split(line + i, ',');
	if (!rgb)
		exit_game(game, "Error\nMalloc faild for colors", 1);
	validate_and_set_rgb(game, color, rgb);
}

static void	process_color_line(t_game *game, char *line, int *map_start)
{
	if (is_color_chr(line))
	{
		set_color_value(game, line);
		if (*map_start)
			exit_game(game, "Error\nColors must be set before the map", 1);
	}
	else if (!is_texture(line) && is_map_chr(line[0]))
		*map_start = 1;
	else if (!is_texture(line))
		exit_game(game, "Error\nInvalid line in map", 1);
}

void	validate_colors(t_game *game)
{
	int		i;
	char	**line;
	int		map_start;

	i = 0;
	map_start = 0;
	line = game->map.grid;
	while (line[i])
	{
		if (!line[i][0] || is_spaces(line[i]))
		{
			i++;
			continue ;
		}
		process_color_line(game, line[i], &map_start);
		i++;
	}
	if (game->ceiling.set != 1 || game->floor.set != 1)
		exit_game(game, "Error\nFloor and ceiling colors must set once", 1);
}
