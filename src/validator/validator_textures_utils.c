/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_textures_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:00:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/30 17:25:21 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_texture(t_textures *textures, char *line)
{
	int	i;

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

void	check_texture_file(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_game(game, "Error\nCannot open texture file", 1);
	close(fd);
}

void	set_texture_path(t_game *game, char *line)
{
	char	**texture_path;
	int		i;

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
		exit_game(game, "Error\nMalloc failed for texture path", 1);
	if (**texture_path == '\0')
		exit_game(game, "Error\nEmpty texture path", 1);
	if (ft_strlen(*texture_path) < 4 || ft_strncmp(*texture_path
			+ ft_strlen(*texture_path) - 4, ".xpm", 4))
		exit_game(game, "Error\nTexture file must have .xpm extension", 1);
	check_texture_file(game, *texture_path);
}
