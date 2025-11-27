/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 02:47:59 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 16:56:28 by dikhalil         ###   ########.fr       */
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

static void	set_player_direction(t_player *player, char direction)
{
    if (direction == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (direction == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (direction == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (direction == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
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
            if (line[i][j] == 'N' || line[i][j] == 'S'
                || line[i][j] == 'E' || line[i][j] == 'W')
            {
                count++;
                player->pos_x = j + 0.5;
                player->pos_y = i + 0.5;
                set_player_direction(player, line[i][j]);
                line[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    return (count);
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
    if (!flood_fill(copy, game->player.pos_x, game->player.pos_y, rows))
    {
        free_map_line(copy);
        return (0);
    }
    free_map_line(copy);
    return (1);
}

void validate_map(t_game *game)
{
    int     i;
    char    **line;
    int     player_count;

    i = 0;
    line = game->map.grid;
    while (line[i] && (is_texture(line[i]) || is_color_chr(line[i]) 
        || !line[i][0] || is_spaces(line[i])))
        i++;
    if (!line[i])
        exit_game(game, "Error\nMap is missing", 1);
    player_count = is_valid_content(&game->player, line + i);
    if (player_count == 0)
        exit_game(game, "Error\nInvalid content in map", 1);
    if (player_count != 1)
        exit_game(game, "Error\nMap must contain one player", 1);
    if (!is_closed(game, line + i))
        exit_game(game, "Error\nMap must be enclosed/surrounded by walls", 1);
}
