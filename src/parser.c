/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:49:45 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/01 23:46:45 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_file_name(char *file)
{
    if (!file || ft_strlen(file) < 4
        || ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
        exit_game(NULL, "Error\nMap file must have a .cub extension", 1);
}

static void count_map_rows(t_map *map)
{
    int fd;
    char *line;
    
    map->rows = 0;
    fd = open(map->map_file, O_RDONLY);
    if (fd < 0)
        exit_game(NULL, "Error\nCannot open map file", 1);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        map->rows++;
        free(line);
    }
    close(fd);
    if (map->rows == 0)
        exit_game(NULL, "Error\nMap file is empty", 1);
}

static void allocate_map(t_game *game)
{
    game->map.grid = malloc(sizeof(char *) * (game->map.rows + 1));
    if (!game->map.grid)
        exit_game(NULL, "Error\nMalloc failed for map grid", 1);
    game->map.cols = malloc(sizeof(int) * game->map.rows);
    if (!game->map.cols)
        exit_game(game, "Error\nMalloc failed for map cols", 1);
}

static void	read_map(t_game *game)
{
    int fd;
    char *line;
    int i;

    i = 0;
    fd = open(game->map.map_file, O_RDONLY);
    if (fd < 0)
        exit_game(NULL, "Error\nCannot open map file", 1);
    while (1)
    {
        line = get_next_line(fd);
		if (!line)
			break ;
        game->map.grid[i] = ft_strtrim(line, " \t\n");
        free(line);
        if (!game->map.grid[i])
        {
            close(fd);
            exit_game(game, "Error\nMalloc faild", 1);
        }
        game->map.cols[i] = ft_strlen(game->map.grid[i]);
        i++;
    }
    game->map.grid[i] = NULL;
    close(fd);
}

void parser(t_game *game)
{
    check_file_name(game->map.map_file);
    count_map_rows(&game->map);
    allocate_map(game);
    read_map(game);
}
