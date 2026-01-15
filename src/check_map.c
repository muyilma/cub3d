#include "../cub3d.h"

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = ft_calloc(map->height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (map->map[i])
	{
		copy[i] = ft_strdup(map->map[i]);
		if (!copy[i])
		{
			free_arr(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(t_map *map, char **copy, int x, int y)
{
	if (x < 0 || y < 0 || y >= map->height
		|| x >= (int)ft_strlen(copy[y]))
	{
		free_arr(copy);
		exit_error(map, "Error\nMap is not closed (Player falls to void)");
	}
	if (copy[y][x] == '1' || copy[y][x] == 'V')
		return ;
	if (copy[y][x] == ' ')
	{
		free_arr(copy);
		exit_error(map, "Error\nMap is not closed (Space found inside)");
	}
	copy[y][x] = 'V';
	flood_fill(map, copy, x + 1, y);
	flood_fill(map, copy, x - 1, y);
	flood_fill(map, copy, x, y + 1);
	flood_fill(map, copy, x, y - 1);
}

static int	check_cell(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y][x];
	if (!ft_strchr("01NSEW ", c))
		exit_error(map, "Error\nInvalid character in map");
	if (ft_strchr("NSEW", c))
	{
		map->p_x = x;
		map->p_y = y;
		map->p_dir = c;
		map->map[y][x] = '0';
		return (1);
	}
	return (0);
}

static void	scan_map(t_map *map)
{
	int	x;
	int	y;
	int	p_count;

	y = 0;
	p_count = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			p_count += check_cell(map, x, y);
			x++;
		}
		y++;
	}
	if (p_count != 1)
		exit_error(map, "Error\nMap must contain exactly one player");
}

void	check_map_validity(t_map *map)
{
	char	**temp_map;

	scan_map(map);
	temp_map = copy_map(map);
	if (!temp_map)
		exit_error(map, "Error\nMalloc failed in check_map");
	flood_fill(map, temp_map, map->p_x, map->p_y);
	free_arr(temp_map);
}
