/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:06:29 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/30 17:39:01 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 600
# define MOVE_SPEED 0.03
# define ROT_SPEED 0.03
# define MOUSE_SENSITIVITY 0.001
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			set;
}				t_color;

typedef struct s_textures
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
}				t_textures;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_ray;

typedef struct s_wall
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_num;
}				t_wall;

typedef struct s_map
{
	char		*map_file;
	char		**grid;
	int			rows;
	int			*cols;
	int			map_start_row;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_mlx
{
	void		*ctx;
	void		*win;
	t_img		imgs[5];

}				t_mlx;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_game
{
	t_mlx		mlx;
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_map		map;
	t_keys		keys;
}				t_game;

int				is_spaces(char *line);

/*------ parser ------*/
void			parser(t_game *game);
void			check_extensions(char *file);
void			store_map_line(t_game *game, char *line, int i, int fd);

/*------ validator ------*/
int				is_texture(char *line);
void			validate_textures(t_game *game);
char			**get_texture(t_textures *textures, char *line);
void			check_texture_file(t_game *game, char *path);
void			set_texture_path(t_game *game, char *line);
int				is_color_chr(char *line);
void			validate_colors(t_game *game);
int				is_number(char **str);
int				count_commas(char *str);
void			validate_and_set_rgb(t_game *game, t_color *color, char **rgb);
int				validate_single_number(char *str);
int				is_map_chr(char c);
void			free_map_line(char **map);
char			**copy_map(char **map, int rows);
int				flood_fill(char **map, int x, int y, int rows);
int				is_valid_cell(char **map, int x, int y, int rows);
int				check_adjacent(char **line, int x, int y, int rows);
int				check_diagonals(char **line, int x, int y, int rows);
int				check_surrounded(char **line, int rows);
void			validate_map(t_game *game);
void			validator(t_game *game);

/*------ render ------*/
void			render(t_game *game);

/*------ draw ------*/
void			draw_game(t_game *game);

/*------ move ------*/
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			strafe_left(t_game *game);
void			strafe_right(t_game *game);

/*------ rotate ------*/
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			rotate_mouse(t_game *game, double angle);

/*------ mouse ------*/
int				mouse_move(int x, int y, t_game *game);

/*------ hooks ------*/
int				key_press(int code, t_game *game);
int				key_release(int code, t_game *game);
int				game_loop(t_game *game);
int				close_window(t_game *game);

/*------ raycasting ------*/
void			cast_rays(t_game *game);
void			load_textures(t_game *game);
void			init_ray(t_ray *ray, t_game *game, int x);
void			set_step_and_side_dist(t_ray *ray, t_game *game);
void			perform_dda(t_ray *ray, t_game *game);
void			calculate_wall_distance(t_ray *ray);
void			init_wall_data(t_wall *wall, t_ray *ray, t_game *game);
void			select_texture(t_wall *wall, t_ray *ray);
void			calculate_texture_x(t_wall *wall, t_game *game);
void			put_pixel(t_game *game, int x, int y, int color);
int				get_texture_color(t_game *game, int tex_num, int tex_x,
					int tex_y);
void			draw_vertical_line(t_game *game, int x, t_wall *wall);

/*------ utils ------*/
int				is_spaces(char *line);
int				ft_strcmp(const char *s1, const char *s2);

/*------ cleanup ------*/
void			free_map_grid(t_game *game);
void			free_map_cols(t_game *game);
void			free_textures(t_game *game);
void			destroy_images(t_game *game);
void			destroy_window(t_game *game);
void			free_game(t_game *game);
void			exit_game(t_game *game, char *msg, int code);

#endif
