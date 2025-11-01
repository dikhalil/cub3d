/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:13:36 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/01 23:16:12 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_game(t_game *game)
{
    
}

void exit_program(t_game *game, char *msg, int status)
{
    if (game)
        free_game(game);
    if (msg)
        ft_putendl_fd(msg, status);
    exit(status);
}