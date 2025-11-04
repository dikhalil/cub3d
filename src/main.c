/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:20:48 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/04 21:54:03 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_spaces(char *line)
{
    int i;

    i = 0;
    if (!line[i])
        return (0);
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}
int main(int argc, char **argv)
{
    t_game game;
    
    if (argc != 2)
        exit_game(NULL, "Error\nTry ./cub3d path/to/map.cub", 1);
    ft_bzero(&game, sizeof(t_game));
    game.map.map_file = argv[1];
    parser(&game);
    validator(&game);
    return (0);
}