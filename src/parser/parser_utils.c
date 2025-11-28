/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:02:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/28 17:02:31 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extensions(char *file)
{
	size_t	len;
	char	*last_slash;
	char	*filename;

	if (!file)
		exit_game(NULL, "Error\nNo map file provided", 1);
	len = ft_strlen(file);
	last_slash = ft_strrchr(file, '/');
	if (last_slash)
		filename = last_slash + 1;
	else
		filename = file;
	if (ft_strcmp(filename, ".cub") == 0)
		exit_game(NULL, "Error\nMap file name is missing", 1);
	if (len < 5 || ft_strcmp(file + len - 4, ".cub") != 0)
		exit_game(NULL, "Error\nInvalid map file extension. Expected .cub", 1);
}

void	process_line(t_game *game, char *line, int i, int fd)
{
	game->map.grid[i] = ft_strtrim(line, "\n");
	free(line);
	if (!game->map.grid[i])
	{
		get_next_line(-1);
		close(fd);
		exit_game(game, "Error\nMalloc faild", 1);
	}
	game->map.cols[i] = ft_strlen(game->map.grid[i]);
}
