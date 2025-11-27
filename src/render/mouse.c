/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:10:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 23:02:20 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	exit_game(game, "Game closed", 0);
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	old_x = -1;
	int			delta_x;
	double		rotation_angle;

	(void)y;
	if (old_x == -1)
	{
		old_x = x;
		return (0);
	}
	delta_x = x - old_x;
	if (delta_x != 0)
	{
		rotation_angle = delta_x * MOUSE_SENSITIVITY;
		rotate_mouse(game, -rotation_angle);
		draw_game(game);
	}
	old_x = x;
	if (x < 100 || x > WIDTH - 100)
	{
		mlx_mouse_move(game->mlx.ctx, game->mlx.win, WIDTH / 2, HEIGHT / 2);
		old_x = WIDTH / 2;
	}
	return (0);
}
