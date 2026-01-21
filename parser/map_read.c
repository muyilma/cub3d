/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:38:19 by omgorege          #+#    #+#             */
/*   Updated: 2026/01/21 12:53:50 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int	get_map_height_array(t_map *map, int i)
{
	int	height;

	height = 0;
	while (map->file_content[i])
	{
		height++;
		i++;
	}
	return (height);
}

void	process_map_content(t_map *map, int i)
{
	int		j;
	char	*line;

	map->height = get_map_height_array(map, i);
	if (map->height == 0)
		exit_error(map, "No map found");
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit_error(map, "Malloc failed");
	j = 0;
	while (map->file_content[i])
	{
		line = ft_strdup(map->file_content[i]);
		if (!line)
			exit_error(map, "Malloc failed");
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		map->map[j] = line;
		i++;
		j++;
	}
	map->map[j] = NULL;
}
