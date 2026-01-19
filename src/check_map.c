#include "../cub3d.h"

static int	check_cell(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y][x];
	if (!ft_strchr("01NSEW ", c))
		exit_error(map, "Invalid character in map");
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

static void check_surroundings(t_map *map, int x, int y)
{
    if (!ft_strchr("0NSEW", map->map[y][x]))
        return ;
    if (y == 0 || !map->map[y + 1] || x == 0 || !map->map[y][x + 1])
        exit_error(map, "Error\nMap is not closed (0 is on the edge)");
    if (x >= (int)ft_strlen(map->map[y - 1]) ||
        x >= (int)ft_strlen(map->map[y + 1]))
        exit_error(map, "Error\nMap is not closed (Gap in neighbor line)");
    if (!ft_strchr("01NSEW", map->map[y][x + 1]) ||
        !ft_strchr("01NSEW", map->map[y][x - 1]) ||
        !ft_strchr("01NSEW", map->map[y + 1][x]) ||
        !ft_strchr("01NSEW", map->map[y - 1][x]))
        exit_error(map, "Error\nMap is not closed (Invalid neighbor around 0)");
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
			check_surroundings(map, x, y);
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
	char	**cpymap;
	scan_map(map);

	cpymap = create_map_copy(map);
	if (!cpymap)
		exit_error(map, "Error\nMalloc failed");

	flood_fill(map, cpymap, map->p_x, map->p_y);
	cpymap_control(map, cpymap);
	free_arr(cpymap);
}
