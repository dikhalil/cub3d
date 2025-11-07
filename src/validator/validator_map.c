/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:04:26 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/07 16:08:11 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_map_chr(char c)
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
            if (!is_map_chr(line[i][j]))
                return (0);
            if (line[i][j] != '1' && line[i][j] != ' ' && line[i][j] != '0')
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

static int is_closed(t_game *game, char **line)
{
    char **copy;
    int rows;

    rows = 0;
    while (line[rows])
        rows++;
    copy = copy_map(line, rows);
    if (!copy)
    	exit_game(game, "Error\nMalloc failed in map copy", 1);
    if (!flood_fill(copy, game->player.x, game->player.y, rows))
    {
        free_map(copy);
        return (0);
    }
    free_map(copy);
    return (1);
}

void validate_map(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i] && (is_texture(line[i]) || is_color_chr(line[i]) || !line[i][0]
    || is_spaces(line[i])))
        i++;
    if (!line[i])
        exit_game(game, "Error\nMap is missing", 1);
    if (!is_valid_content(&game->player, line + i))
        exit_game(game, "Error\nInvalid content in map", 1);
    if (!is_closed(game, line + i))
        exit_game(game, "Error\nMap must be enclosed/surrounded by walls", 1);
}
