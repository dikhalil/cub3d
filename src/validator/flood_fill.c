/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:08:27 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/07 16:10:12 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(char **map)
{
    int i;
    
    i = 0;
    while (map[i])
        free(map[i++]);
    free(map);
}

char **copy_map(char **map, int rows)
{
    char **copy;
    int i;

    i = 0;
    copy = malloc(sizeof(char *) * (rows + 1));
    if (!copy)
        return (NULL);
    while (i < rows)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

int flood_fill(char **map, int x, int y, int rows)
{
	if (x == -1 || y == -1 || x >= (int)ft_strlen(map[y]) || y >= rows)
		return (0);
    if (map[y][x] == '1' || map[y][x] == 'v')
        return (1);
    if (map[y][x] == ' ')
        return (0);
    map[y][x] = 'v';
    if (!flood_fill(map, x + 1, y, rows))
        return (0);
    if (!flood_fill(map, x - 1, y, rows))
        return (0);
    if (!flood_fill(map, x, y + 1, rows)) 
        return (0);
    if (!flood_fill(map, x, y - 1, rows))
        return (0);
    if (!flood_fill(map, x + 1, y - 1, rows))
        return (0);
    if (!flood_fill(map, x - 1, y + 1, rows))
        return (0);
    if (!flood_fill(map, x + 1, y + 1, rows)) 
        return (0);
    if (!flood_fill(map, x - 1, y - 1, rows))
        return (0);
    return (1);
}

