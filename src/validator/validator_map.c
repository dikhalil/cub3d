/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:04:26 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/02 03:23:42 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_map_char(char c)
{
    return (c == '0' || c == '1' ||
            c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || 
            c == ' ');
}

static int is_valid_content(t_player *player, char **line)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        j = 0;
        while (line[i][j])
        {
            if (!is_map_char(line[i][j]))
                return (0);
            if (line[i][j] != '1' && line[i][j] != ' ')
            {
                count++;
                player->dir = line[i][j];
                player->x = j;
                player->y = i;
            }
            j++;
        }
        i++;
    }
    return (count == 1);
}

static int is_valid_cell(char **line, int i, int j, int rows)
{
    if (!line[i])
        return (0);
    if (i == 0 || i == (rows - 1) || j == 0 || j == (ft_strlen(line[i]) - 1))
        return (0);
    if (!line[i - 1] || !line[i + 1])
        return (0);
     if (j >= ft_strlen(line[i - 1]) || j >= ft_strlen(line[i + 1]))
        return (0);
    if (line[i - 1][j] == ' ' || line[i + 1][j] == ' ' ||
        line[i][j - 1] == ' ' || line[i][j + 1] == ' ')
        return (0);
    return (1);
}

static int is_closed(char **line)
{
    int i;
    int j;
    int rows;
    
    i = 0;
    j = 0;
    rows = 0;
    while (line[rows])
        rows++;
    while (line[i])
    {
        j = 0;
        while (line[i][j])
        {
            if (line[i][j] != '1' && line[i][j] != ' ')
            {
             
                if (!is_valid_cell(line, i, j, rows))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void validate_map(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i] && !is_texture(line[i]) && !is_color_char(line[i]) && !is_map_chr(line[i][0]))
        i++;
    if (!line[i])
        exit_game(game, "Error\nMap is missing", 1);
    if (!is_valid_content(&game->player, line + i))
        exit_game(game, "Error\nInvalid content in map", 1);
    if (!is_closed(line + i))
        exit_game(game, "Error\nMap must be enclosed/surrounded by walls", 1);
}
