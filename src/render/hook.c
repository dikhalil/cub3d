/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:51:06 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 17:06:38 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int code, t_game *game)
{
    if (code == KEY_W || code == KEY_UP)
        game->keys.w = 1;
    else if (code == KEY_S || code == KEY_DOWN)
        game->keys.s = 1;
    else if (code == KEY_A)
        game->keys.a = 1;
    else if (code == KEY_D)
        game->keys.d = 1;
    else if (code == KEY_LEFT)
        game->keys.left = 1;
    else if (code == KEY_RIGHT)
        game->keys.right = 1;
    else if (code == KEY_ESC)
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

int	game_loop(t_game *game)
{
    int	moved;

    moved = 0;
    if (game->keys.w)
    {
        move_forward(game);
        moved = 1;
    }
    if (game->keys.s)
    {
        move_backward(game);
        moved = 1;
    }
    if (game->keys.a)
    {
        strafe_left(game);
        moved = 1;
    }
    if (game->keys.d)
    {
        strafe_right(game);
        moved = 1;
    }
    if (game->keys.left)
    {
        rotate_left(game);
        moved = 1;
    }
    if (game->keys.right)
    {
        rotate_right(game);
        moved = 1;
    }
    if (moved)
        draw_game(game);
    return (0);
}

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
