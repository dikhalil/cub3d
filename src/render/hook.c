/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:51:06 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/25 23:51:24 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int key_hook(int code, t_game *game)
{
    if (code == KEY_W || code == KEY_UP)
		move_up(game);
	else if (code == KEY_A || code == KEY_LEFT)
		move_left(game);
	else if (code == KEY_S || code == KEY_DOWN)
		move_down(game);
	else if (code == KEY_D || code == KEY_RIGHT)
		move_right(game);
	else if (code == KEY_ESC)
		exit_game(game, "Game closed", 0);
    return (0);
}

int close_window(t_game *game)
{
    exit_game(game, "game closed", 0);
    return (0);
}
