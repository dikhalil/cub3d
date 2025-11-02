/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:01:36 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/02 03:02:46 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_color_chr(char c)
{
    return (c == 'F' || c == 'C');
}

static int	is_number(char **str)
{
	int	i;
    int j;

	i = 0;
    j = 0;
    while (str[i])
    { 
        j = 0;
        while (str[i][j] == ' ' || str[i][j] == '\t')
            j++;
        if (!str[i][j])
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

static t_color *get_color(t_game *game, char c)
{
    if (c == 'F')
        return (&game->floor);
    return (&game->ceiling);
}

static void set_color_value(t_game *game, char *line)
{
    t_color *color;
    char **rgb;
    int i;

    color = get_color(game, line[0]);
    rgb = ft_split(line + 1, ',');
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
}

void validate_colors(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i])
    {
        if (is_color_chr(line[i][0]))
            set_color_value(game, line[i]);
        else if (is_map_char(line[i][0]))
            break;
        else if (!is_texture(line[i]) && line[i][0])
            exit_game(game, "Error\nInvalid line in map", 1);
        i++;
    }
    if (game->ceiling.set  != 1|| game->floor.set != 1)
        exit_game(game, "Error\nMissing floor or ceiling color", 1);
}

