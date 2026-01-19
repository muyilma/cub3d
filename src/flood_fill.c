#include "../cub3d.h"

char	**create_map_copy(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map->map[i])
	{
		copy[i] = ft_strdup(map->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(t_map *map, char **cpymap, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || !cpymap[y])
		return ;
	if (x >= (int)ft_strlen(cpymap[y]))
		return ;
	if (cpymap[y][x] == ' ' || cpymap[y][x] == '\t' || 
		cpymap[y][x] == '\n' || cpymap[y][x] == 'F')
		return ;
	cpymap[y][x] = 'F';
	flood_fill(map, cpymap, x + 1, y);
	flood_fill(map, cpymap, x - 1, y);
	flood_fill(map, cpymap, x, y + 1);
	flood_fill(map, cpymap, x, y - 1);
}

void	cpymap_control(t_map *map, char **cpymap)
{
	int	y;
	int	x;

	y = 0;
	while (cpymap[y])
	{
		x = 0;
		while (cpymap[y][x])
		{
			if (cpymap[y][x] != '\t' && cpymap[y][x] != 'F' 
				&& cpymap[y][x] != ' ' && cpymap[y][x] != '\n')
			{
				free_arr(cpymap);
				exit_error(map, "Multiple map errors");
			}
			x++;
		}
		y++;
	}
}
