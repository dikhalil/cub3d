/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:06:29 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/26 01:23:54 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_color
{
    int r;
    int g;
    int b;
    int set;
} t_color;

typedef struct s_textures
{
    char *north_path;
    char *south_path;
    char *west_path;
    char *east_path;
} t_textures;

typedef struct s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_map
{
    char *map_file;
    char **grid;
    int rows;
    int *cols;
} t_map;

typedef struct s_img
{
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
} t_img;

typedef struct s_mlx
{
    void *ctx;
    void *win;
    t_img  imgs[5];
    
} t_mlx;

typedef struct s_game
{
    t_mlx mlx;
    t_textures textures;
    t_color floor;
    t_color ceiling;
    t_player player;
    t_map map;
} t_game;

int is_spaces(char *line);

/*------ parser ------*/
void parser(t_game *game);

/*------ validator ------*/
int is_texture(char *line);
void validate_textures(t_game *game);
int is_color_chr(char *line);
void validate_colors(t_game *game);
int is_map_chr(char c);
void free_map_line(char **map);
char **copy_map(char **map, int rows);
int flood_fill(char **map, int x, int y, int rows);
void validate_map(t_game *game);
void validator(t_game *game);

/*------ render ------*/
void render(t_game *game);

/*------ draw ------*/
void draw_game(t_game *game);

/*------ move ------*/
void move_up(t_game *game);
void move_down(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);

/*------ hook ------*/
int key_hook(int code, t_game *game);
int close_window(t_game *game);

/*------ exit ------*/
void free_game(t_game *game);
void exit_game(t_game *game, char *msg, int status);

#endif
