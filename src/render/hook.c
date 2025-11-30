/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:51:06 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/30 17:23:56 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int code, t_game *game)
{
	if (code == KEY_W || code == KEY_UP)
		game->keys.w = 1;
	else if (code == KEY_S)
		game->keys.s = 1;
	else if (code == KEY_A)
		game->keys.a = 1;
	else if (code == KEY_D)
		game->keys.d = 1;
	else if (code == KEY_LEFT)
		game->keys.left = 1;
	else if (code == KEY_RIGHT)
		game->keys.right = 1;
	else if (code == KEY_ESC || code == KEY_Q)
		exit_game(game, "Game closed", 0);
	return (0);
}

int	key_release(int code, t_game *game)
{
	if (code == KEY_W || code == KEY_UP)
		game->keys.w = 0;
	else if (code == KEY_S || code == KEY_DOWN)
		game->keys.s = 0;
	else if (code == KEY_A)
		game->keys.a = 0;
	else if (code == KEY_D)
		game->keys.d = 0;
	else if (code == KEY_LEFT)
		game->keys.left = 0;
	else if (code == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

static int	handle_movement(t_game *game)
{
	int	moved;

	moved = 0;
	if (game->keys.w && ++moved)
		move_forward(game);
	if (game->keys.s && ++moved)
		move_backward(game);
	if (game->keys.a && ++moved)
		strafe_left(game);
	if (game->keys.d && ++moved)
		strafe_right(game);
	return (moved);
}

static int	handle_rotation(t_game *game)
{
	int	moved;

	moved = 0;
	if (game->keys.left && ++moved)
		rotate_left(game);
	if (game->keys.right && ++moved)
		rotate_right(game);
	return (moved);
}

int	game_loop(t_game *game)
{
	int	moved;

	moved = handle_movement(game);
	moved += handle_rotation(game);
	if (moved)
		draw_game(game);
	return (0);
}
