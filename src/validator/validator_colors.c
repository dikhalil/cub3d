/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:01:36 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/08 12:49:19 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_color_chr(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (line[i] == 'F' || line[i] == 'C');
}

static int	is_number(char **str)
{
	int	i;
    int j;

	i = 0;
    j = 0;
    if (!str || !*str)
        return (0);
    while (str[i])
    {
        j = 0;
        if (!str[i][0])
            return (0);
        if (str[i][j] == ' ' || str[i][j] == '\t')
            return (0);
        if (str[i][j] == '-' || str[i][j] == '+')
            j++;
        if (!str[i][j])
            return (0);
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (0);
            j++;
        }
        i++;
    }
	return (1);
}

static t_color *get_color(t_game *game, char *line)
{
    if (*line == 'F')
        return (&game->floor);
    return (&game->ceiling);
}
static void set_color_value(t_game *game, char *line)
{
    t_color *color;
    char **rgb;
    int i;
	int j;
	int count;

    i = 0;
	j = 0;
	count = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    color = get_color(game, line + i);
    i++;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	j = i;
	while (line[j])
	{
		if (line[j] == ',')
			count++;
		j++;
	}
	if (count != 2)
       exit_game(game, "Error\nInvalid color format", 1);
    rgb = ft_split(line + i, ',');
    if (!rgb)
        exit_game(game, "Error\nMalloc faild for colors", 1);
    if(!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] || !is_number(rgb))
    {
       free_split(rgb);
       exit_game(game, "Error\nInvalid color format", 1);
    }
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    free_split(rgb);
    if (color->r < 0 || color->r > 255 ||
        color->g < 0 || color->g > 255 ||
        color->b < 0 || color->b > 255)
        exit_game(game, "Error\nColor value out of range", 1);
    color->set++;
    if (color->set > 1)
		exit_game(game, "Error\nDuplicate color", 1);
}

void validate_colors(t_game *game)
{
    int i;
    char **line;
    int map_start;

    i = 0;
    map_start = 0;
    line = game->map.grid;
    while (line[i])
    {
        if (!line[i][0] || is_spaces(line[i]))
        {
            i++;
            continue;
        }
        if (is_color_chr(line[i]))
        {
            set_color_value(game, line[i]);
            if (map_start)
                exit_game(game, "Error\nColors must be set before the map", 1);
        }
        else if (!is_texture(line[i]) && is_map_chr(line[i][0]))
            map_start = 1;
        else if (!is_texture(line[i]))
            exit_game(game, "Error\nInvalid line in map", 1);
        i++;
    }
    if (game->ceiling.set != 1 || game->floor.set != 1)
        exit_game(game, "Error\nFloor and ceiling colors must set once", 1);
}

