/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:00:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 22:58:31 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_texture(t_wall *wall, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			wall->tex_num = 4;
		else
			wall->tex_num = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			wall->tex_num = 2;
		else
			wall->tex_num = 1;
	}
}

void	calculate_texture_x(t_wall *wall, t_game *game)
{
	wall->tex_x = (int)(wall->wall_x
			* (double)game->mlx.imgs[wall->tex_num].width);
	if ((wall->tex_x < 0 || wall->tex_x >= game->mlx.imgs[wall->tex_num].width))
		wall->tex_x = 0;
}

int	get_texture_color(t_game *game, int tex_num, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= game->mlx.imgs[tex_num].width || tex_y < 0
		|| tex_y >= game->mlx.imgs[tex_num].height)
		return (0);
	pixel = game->mlx.imgs[tex_num].addr + (tex_y
			* game->mlx.imgs[tex_num].line_length + tex_x
			* (game->mlx.imgs[tex_num].bpp / 8));
	return (*(unsigned int *)pixel);
}
