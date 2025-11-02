/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 03:00:18 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/02 03:02:53 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_texture(char *line)
{
    if (!line || !*line)
		return (0);
    if (ft_strncmp(line, "NO", 2) == 0 ||
        ft_strncmp(line, "SO", 2) == 0 ||
        ft_strncmp(line, "WE", 2) == 0 ||
        ft_strncmp(line, "EA", 2) == 0)
        return (1);
    return (0);
}

static char **get_texture(t_textures *textures, char *line)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        return (&textures->north_path);
    else if (ft_strncmp(line, "SO", 2) == 0)
        return (&textures->south_path);
    else if (ft_strncmp(line, "WE", 2) == 0)
        return (&textures->west_path);
    else if (ft_strncmp(line, "EA", 2) == 0)
        return (&textures->east_path);
    else
        return (NULL);
}

static void	set_texture_path(t_game *game, char *line)
{
    char **texture_path;

    texture_path = get_texture(&game->textures, line);
    if (!texture_path)
        return ;
    if (*texture_path)
		exit_game(game, "Error\nDuplicate texture path\n", 1);
	*texture_path = ft_strtrim(line + 2, " \t\n");
	if (!*texture_path)
		exit_game(game, "Error\nMalloc faild for texture path\n", 1);
    if (**texture_path == '\0')
		exit_game(game, "Error\nEmpty texture path\n", 1);
}

void validate_textures(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i])
    {
        line[i] = game->map.grid[i];
        if (is_texture(line[i]))
            set_texture_path(game, line[i]);
        else if (is_map_char(line[i][0]))
            break;
        else if (!is_color_chr(line[i][0]) && line[i][0])
            exit_game(game, "Error\nInvalid line in map", 1);
        i++; 
    }
    if (!game->textures.north_path || !game->textures.south_path
    || !game->textures.west_path || !game->textures.east_path)
        exit_game(game, "Error\nMissing one or more wall textures", 1);
}
