/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:02:58 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/04 23:01:06 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_texture(char *line)
{
    int i;

    i = 0;
    if (!line || !*line)
		return (0);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (ft_strncmp(line + i, "NO", 2) == 0 ||
        ft_strncmp(line + i, "SO", 2) == 0 ||
        ft_strncmp(line + i, "WE", 2) == 0 ||
        ft_strncmp(line + i, "EA", 2) == 0)
        return (1);
    return (0);
}

static char **get_texture(t_textures *textures, char *line)
{
    int i;

    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (ft_strncmp(line + i, "NO", 2) == 0)
        return (&textures->north_path);
    else if (ft_strncmp(line + i, "SO", 2) == 0)
        return (&textures->south_path);
    else if (ft_strncmp(line + i, "WE", 2) == 0)
        return (&textures->west_path);
    else if (ft_strncmp(line + i, "EA", 2) == 0)
        return (&textures->east_path);
    else
        return (NULL);
}

static void	set_texture_path(t_game *game, char *line)
{
    char **texture_path;
    int i;

    i = 0;
    texture_path = get_texture(&game->textures, line);
    if (!texture_path)
        return ;
    if (*texture_path)
		exit_game(game, "Error\nDuplicate texture path", 1);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    *texture_path = ft_strtrim(line + i + 2, " \t\n");
	if (!*texture_path)
		exit_game(game, "Error\nMalloc faild for texture path", 1);
    if (**texture_path == '\0')
		exit_game(game, "Error\nEmpty texture path", 1);
}

void validate_textures(t_game *game)
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
        if (is_texture(line[i]))
        {
            set_texture_path(game, line[i]);
            if (map_start)
                exit_game(game, "Error\nTextures must be set before the map", 1);
        }
        else if (!is_color_chr(line[i]) && is_map_chr(line[i][0]))
            map_start = 1;
        else if (!is_color_chr(line[i]))
            exit_game(game, "Error\nInvalid line in map", 1);
        i++; 
    }
    if (!game->textures.north_path || !game->textures.south_path
    || !game->textures.west_path || !game->textures.east_path)
        exit_game(game, "Error\nEvrey wall texture must be set once", 1);
}