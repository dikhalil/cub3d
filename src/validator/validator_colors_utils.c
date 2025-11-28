/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_colors_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dikhalil <dikhalil@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:30:00 by dikhalil          #+#    #+#             */
/*   Updated: 2025/11/28 17:11:00 by dikhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	validate_single_number(char *str)
{
	int	j;

	j = 0;
	if (!str[0] || str[j] == ' ' || str[j] == '\t')
		return (0);
	if (str[j] == '-' || str[j] == '+')
		j++;
	if (!str[j])
		return (0);
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
			return (0);
		j++;
	}
	return (1);
}

void	validate_and_set_rgb(t_game *game, t_color *color, char **rgb)
{
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3] || !is_number(rgb))
	{
		free_split(rgb);
		exit_game(game, "Error\nInvalid color format", 1);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		exit_game(game, "Error\nColor value out of range", 1);
	color->set++;
	if (color->set > 1)
		exit_game(game, "Error\nDuplicate color", 1);
}
