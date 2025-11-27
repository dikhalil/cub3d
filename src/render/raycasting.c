/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:28:59 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/27 16:57:30 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *ray, t_game *game, int x)
{
    ray->camera_x = 2 * x / (double)WIDTH - 1;
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
    ray->map_x = (int)game->player.pos_x;
    ray->map_y = (int)game->player.pos_y;
    if (ray->ray_dir_x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    if (ray->ray_dir_y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    ray->hit = 0;
}

static void	set_step_and_side_dist(t_ray *ray, t_game *game)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
    }
}

static void	perform_dda(t_ray *ray, t_game *game)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_y >= 0 && ray->map_y < game->map.rows
            && ray->map_x >= 0 && ray->map_x < game->map.cols[ray->map_y])
        {
            if (game->map.grid[ray->map_y][ray->map_x] == '1')
                ray->hit = 1;
        }
        else
            ray->hit = 1;
    }
}

static void	calculate_wall_distance(t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else
        ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	init_wall_data(t_wall *wall, t_ray *ray, t_game *game)
{
    wall->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    wall->draw_start = -wall->line_height / 2 + HEIGHT / 2;
    if (wall->draw_start < 0)
        wall->draw_start = 0;
    wall->draw_end = wall->line_height / 2 + HEIGHT / 2;
    if (wall->draw_end >= HEIGHT)
        wall->draw_end = HEIGHT - 1;
    if (ray->side == 0)
        wall->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    wall->wall_x -= floor(wall->wall_x);
}

static void	select_texture(t_wall *wall, t_ray *ray)
{
    if (ray->side == 0)  // Vertical wall (East/West)
    {
        if (ray->ray_dir_x > 0)
            wall->tex_num = 4;  // EAST texture
        else
            wall->tex_num = 3;  // WEST texture
    }
    else  // Horizontal wall (North/South)
    {
        if (ray->ray_dir_y > 0)
            wall->tex_num = 2;  // SOUTH texture
        else
            wall->tex_num = 1;  // NORTH texture
    }
}

static void	calculate_texture_x(t_wall *wall, t_game *game)
{
    wall->tex_x = (int)(wall->wall_x * (double)game->mlx.imgs[wall->tex_num].width);
    if ((wall->tex_x < 0 || wall->tex_x >= game->mlx.imgs[wall->tex_num].width))
        wall->tex_x = 0;
}

static void	put_pixel(t_game *game, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = game->mlx.imgs[0].addr + (y * game->mlx.imgs[0].line_length
            + x * (game->mlx.imgs[0].bpp / 8));
    *(unsigned int *)dst = color;
}

static int	get_texture_color(t_game *game, int tex_num, int tex_x, int tex_y)
{
    char	*pixel;

    if (tex_x < 0 || tex_x >= game->mlx.imgs[tex_num].width
        || tex_y < 0 || tex_y >= game->mlx.imgs[tex_num].height)
        return (0);
    pixel = game->mlx.imgs[tex_num].addr
        + (tex_y * game->mlx.imgs[tex_num].line_length
            + tex_x * (game->mlx.imgs[tex_num].bpp / 8));
    return (*(unsigned int *)pixel);
}

static void	draw_vertical_line(t_game *game, int x, t_wall *wall)
{
    int		y;
    int		tex_y;
    double	step;
    double	tex_pos;
    int		color;

    step = 1.0 * game->mlx.imgs[wall->tex_num].height / wall->line_height;
    tex_pos = (wall->draw_start - HEIGHT / 2 + wall->line_height / 2) * step;
    y = 0;
    while (y < HEIGHT)
    {
        if (y < wall->draw_start)
            put_pixel(game, x, y, (game->ceiling.r << 16)
                | (game->ceiling.g << 8) | game->ceiling.b);
        else if (y >= wall->draw_start && y <= wall->draw_end)
        {
            tex_y = (int)tex_pos & (game->mlx.imgs[wall->tex_num].height - 1);
            tex_pos += step;
            color = get_texture_color(game, wall->tex_num, wall->tex_x, tex_y);
            put_pixel(game, x, y, color);
        }
        else
            put_pixel(game, x, y, (game->floor.r << 16)
                | (game->floor.g << 8) | game->floor.b);
        y++;
    }
}

void	cast_rays(t_game *game)
{
    t_ray	ray;
    t_wall	wall;
    int		x;

    x = 0;
    while (x < WIDTH)
    {
        init_ray(&ray, game, x);
        set_step_and_side_dist(&ray, game);
        perform_dda(&ray, game);
        calculate_wall_distance(&ray);
        init_wall_data(&wall, &ray, game);
        select_texture(&wall, &ray);
        calculate_texture_x(&wall, game);
        draw_vertical_line(game, x, &wall);
        x++;
    }
}