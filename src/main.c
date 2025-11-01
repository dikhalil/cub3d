/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:20:48 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/01 23:12:24 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;
    
    if (argc != 2)
        exit_game(&game, "Error\nTry ./cub3d path/to/map.cub", 1);
    bzero(game, sizeof(t_game));
    game.map.map_file = argv[1];
    parser(&game);
    validator(&game);
    return (0);
}