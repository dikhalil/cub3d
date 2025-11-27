/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:00:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 22:59:49 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->mlx.imgs[0].addr + (y * game->mlx.imgs[0].line_length
			+ x * (game->mlx.imgs[0].bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_wall_data(t_wall *wall, t_ray *ray, t_game *game)
{
	wall->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + HEIGHT / 2;
	if (wall->draw_end >= HEIGHT)
		wall->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		wall->wall_x = game->player.pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		wall->wall_x = game->player.pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	wall->wall_x -= floor(wall->wall_x);
}

static void	draw_wall_pixel(t_game *game, int x, int y, t_wall *wall)
{
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * game->mlx.imgs[wall->tex_num].height / wall->line_height;
	tex_pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) * step;
	tex_pos += step * (y - wall->draw_start);
	tex_y = (int)tex_pos & (game->mlx.imgs[wall->tex_num].height - 1);
	color = get_texture_color(game, wall->tex_num, wall->tex_x, tex_y);
	put_pixel(game, x, y, color);
}

void	draw_vertical_line(t_game *game, int x, t_wall *wall)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < wall->draw_start)
			put_pixel(game, x, y, (game->ceiling.r << 16)
				| (game->ceiling.g << 8) | game->ceiling.b);
		else if (y >= wall->draw_start && y <= wall->draw_end)
			draw_wall_pixel(game, x, y, wall);
		else
			put_pixel(game, x, y, (game->floor.r << 16)
				| (game->floor.g << 8) | game->floor.b);
		y++;
	}
}
