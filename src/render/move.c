/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:33:15 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/28 14:51:45 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map.rows)
		return (0);
	if (map_x < 0 || map_x >= game->map.cols[map_y])
		return (0);
	if (game->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}
