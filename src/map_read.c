#include "../cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

static int	get_map_height(char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	int		height;
	int		map_started;

	height = 0;
	map_started = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_error(map, ERR_FILE);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!map_started && is_map_line(line))
			map_started = 1;
		if (map_started)
			height++;
		free(line);
	}
	close(fd);
	return (height);
}

static void	fill_map_array(char *file_path, t_map *map, int	i)
{
	int		fd;
	char	*line;
	int		map_started;

	map_started = 0;
	fd = open(file_path, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!map_started && is_map_line(line))
			map_started = 1;
		if (map_started)
		{
			if (ft_strchr(line, '\n'))
				*ft_strchr(line, '\n') = '\0';
			map->map[i++] = line;
		}
		else
			free(line);
	}
	close(fd);
    map->map[i] = NULL;
}

void	read_map(char *file_path, t_map *map)
{
	map->height = get_map_height(file_path, map);
	if (map->height == 0)
		exit_error(map, "Error\nNo map found");
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit_error(map, "Error\nMalloc failed");
	fill_map_array(file_path, map, 0);
}
