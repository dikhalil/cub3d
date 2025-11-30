/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:00:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/30 17:27:40 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_cell(char **map, int x, int y, int rows)
{
	if (y < 0 || y >= rows)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ')
		return (0);
	return (1);
}

int	check_adjacent(char **line, int x, int y, int rows)
{
	if (!is_valid_cell(line, x + 1, y, rows))
		return (0);
	if (!is_valid_cell(line, x - 1, y, rows))
		return (0);
	if (!is_valid_cell(line, x, y + 1, rows))
		return (0);
	if (!is_valid_cell(line, x, y - 1, rows))
		return (0);
	return (1);
}

int	check_diagonals(char **line, int x, int y, int rows)
{
	if (!is_valid_cell(line, x + 1, y + 1, rows))
		return (0);
	if (!is_valid_cell(line, x - 1, y + 1, rows))
		return (0);
	if (!is_valid_cell(line, x + 1, y - 1, rows))
		return (0);
	if (!is_valid_cell(line, x - 1, y - 1, rows))
		return (0);
	return (1);
}

int	check_surrounded(char **line, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows && line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == '0')
			{
				if (!check_adjacent(line, j, i, rows))
					return (0);
				if (!check_diagonals(line, j, i, rows))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
