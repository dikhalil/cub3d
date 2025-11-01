/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:33:50 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/02 01:28:53 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char **get_texture(t_textures *textures, char *line)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        return (&textures->north_path);
    else if (ft_strncmp(line, "SO", 2) == 0)
        return (&textures->south_path);
    else if (ft_strncmp(line, "WE", 2) == 0)
        return (&textures->west_path);
    else if (ft_strncmp(line, "EA", 2) == 0)
        return (&textures->east_path);
    else
        return (NULL);
}

static void	set_texture_path(t_game *game, char *line)
{
    char **texture_path;

    texture_path = get_texture(&game->textures, line);
    if (!texture_path)
        return ;
    if (*texture_path)
		exit_game(game, "Error\nDuplicate texture path\n", 1);
	*texture_path = ft_strtrim(line + 2, " \t\n");
	if (!*texture_path)
		exit_game(game, "Error\nMalloc faild for texture path\n", 1);
    if (*texture_path[0] == '\0')
		exit_game(game, "Error\nEmpty texture path\n", 1);
}



static int is_color_chr(char c)
{
    return (c == 'F' || c == 'C');
}
static int is_texture(char *line)
{
    if (!line || !*line)
		return (0);
    if (ft_strncmp(line, "NO", 2) == 0 ||
        ft_strncmp(line, "SO", 2) == 0 ||
        ft_strncmp(line, "WE", 2) == 0 ||
        ft_strncmp(line, "EA", 2) == 0)
        return (1);
    return (0);
}
static void validate_textures(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i])
    {
        line[i] = game->map.grid[i];
        if (is_texture(line[i]))
            set_texture_path(game, line[i]);
        else if (is_map_char(line[i][0]))
            break;
        else if (!is_color_chr(line[i][0]) && line[i][0])
            exit_game(game, "Error\nInvalid line in map", 1);
        i++; 
    }
    if (!game->textures.north_path || !game->textures.south_path
    || !game->textures.west_path || !game->textures.east_path)
        exit_game(game, "Error\nMissing one or more wall textures", 1);
}
static int	is_number(char **str)
{
	int	i;
    int j;

	i = 0;
    j = 0;
    while (str[i])
    { 
        j = 0;
        while (str[i][j] == ' ' || str[i][j] == '\t')
            j++;
        if (!str[i][j])
            return (0);
        if (str[i][j] == '-' || str[i][j] == '+')
            j++;
        if (!str[i][j])
            return (0);
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (0);
            j++;
        }
        i++;
    }
	return (1);
}
static t_color *get_color(t_game *game, char c)
{
    if (c == 'F')
        return (&game->floor);
    return (&game->ceiling);
}
static void set_color_value(t_game *game, char *line)
{
    t_color *color;
    char **rgb;
    int i;

    color = get_color(game, line[0]);
    rgb = ft_split(line + 1, ',');
    if (!rgb)
        exit_game(game, "Error\nMalloc faild for colors", 1);
    if(!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] || !is_number(rgb))
    {
       free_split(rgb);
       exit_game(game, "Error\nInvalid color format", 1);
    }
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    free_split(rgb);
    if (color->r < 0 || color->r > 255 ||
        color->g < 0 || color->g > 255 ||
        color->b < 0 || color->b > 255)
        exit_game(game, "Error\nColor value out of range", 1);
    color->set++;
}

static void validate_colors(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i])
    {
        if (is_color_chr(line[i][0]))
            set_color_value(game, line[i]);
        else if (is_map_char(line[i][0]))
            break;
        else if (!is_texture(line[i]) && line[i][0])
            exit_game(game, "Error\nInvalid line in map", 1);
        i++;
    }
    if (game->ceiling.set  != 1|| game->floor.set != 1)
        exit_game(game, "Error\nMissing floor or ceiling color", 1);
}

static int is_map_char(char c)
{
    return (c == '0' || c == '1' ||
            c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || 
            c == ' ');
}

static int is_valid_chrs(char **line)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!line || !*line || !**line)
        return (0);
    while (line[i])
    {
        j = 0;
        while (line[i][j])
        {
            if (!is_map_char(line[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

static int is_one_player(t_player *player, char **line)
{
    int i;
    int j;
    int count;
    
    i = 0;
    j = 0;
    count = 0;
    while (line[i])
    {
        while (line[i][j])
        {
            if (line[i][j] == 'N' || line[i][j] == 'S' 
                || line[i][j] == 'E' || line[i][j] == 'W')
                {
                    count++;
                    player->dir = 
                    
                }
        }
        
            
        
    }
    
}
static int is_closed(t_map *, char **line)
{
    int i;
    int j;
    int rows;
    
    i = 0;
    j = 0;
    rows = 0;
    while (line[rows])
        rows++;
    while (line[0][j])
    {
        if ((line[0][j] != 1 && line[0][j] != ' ') ||
            (line[rows - 1][j] != 1 && line[rows - 1][j] != ' '))
        
    }
    return (1);
}
static void validate_map(t_game *game)
{
    int i;
    char **line;

    i = 0;
    line = game->map.grid;
    while (line[i] && !is_texture(line[i]) && !is_color(line[i]) && !is_map_chr(line[i][0]))
        i++;
    if (!line[i])
        exit_game(game, "Error\nMap is missing", 1);
    if (!is_valid_chrs(line + i))
        exit_game(game, "Error\nInvalid character in map", 1);
    if (!is_closed(&game->map, line + i))
        exit_game(game, "Error\nMap must be enclosed/surrounded by walls", 1);
    if (!is_one_player(&game->player, line + i))
        exit_game(game, "Error\nMap must have exactly 1 player", 1);

}

void validator(t_game *game)
{
    validate_textures(game);
    validate_colors(game);
    validate_map(game);
}