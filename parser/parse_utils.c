/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:38:22 by omgorege          #+#    #+#             */
/*   Updated: 2026/01/21 12:53:57 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

static int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || str[0] == '\n')
		return (0);
	if (str[0] == '0' && (ft_isdigit(str[1])))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	valid_commas(char *line, t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line[0] == ',')
		exit_error(map, "Invalid comma format in color");
	while (line[i])
	{
		if (line[i] == ',')
		{
			count++;
			if (line[i + 1] == ',')
				exit_error(map, "Invalid comma format in color");
		}
		i++;
	}
}

static int	char_to_int_rgb(char **rgb, t_map *map)
{
	int	c[3];

	if ((ft_strlen(rgb[0]) > 3) && (ft_strlen(rgb[1]) > 3)
		&& (ft_strlen(rgb[2]) > 3))
	{
		free_arr(rgb);
		exit_error(map, "Invalid color format (Must be R,G,B)");
	}
	c[0] = ft_atoi(rgb[0]);
	c[1] = ft_atoi(rgb[1]);
	c[2] = ft_atoi(rgb[2]);
	free_arr(rgb);
	if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255 || c[2] < 0
		|| c[2] > 255)
		exit_error(map, "Color values must be between 0 and 255");
	return ((c[0] << 16) | (c[1] << 8) | c[2]);
}

int	parse_rgb(char *line, t_map *map)
{
	char	**rgb;

	valid_commas(line, map);
	rgb = ft_split(line, ',');
	if (!rgb || get_arr_len(rgb) != 3)
	{
		free_arr(rgb);
		exit_error(map, "Invalid color format (Must be R,G,B)");
	}
	if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
	{
		free_arr(rgb);
		exit_error(map, "Color values must be numeric");
	}
	return (char_to_int_rgb(rgb, map));
}
