/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:06:29 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/08 12:25:38 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <mlx.h>
#include "../libft/libft.h"

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
    int x;
    int y;
    char dir;
} t_player;

typedef struct s_map
{
    char *map_file;
    char **grid;
    int rows;
    int *cols;
} t_map;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    int win_width;
    int win_height;
} t_mlx;

typedef struct s_game
{
    t_mlx mlx_data;
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
void free_map(char **map);
char **copy_map(char **map, int rows);
int flood_fill(char **map, int x, int y, int rows);
void validate_map(t_game *game);
void validator(t_game *game);

/*------ exit ------*/
void exit_game(t_game *game, char *msg, int status);

#endif
