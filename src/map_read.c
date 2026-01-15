#include "../cub3d.h"

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

static int	check_map_gap(char *line, int *st, int *end)
{
	if (!*st && is_map_line(line))
		*st = 1;
	if (*st && is_empty_line(line))
		*end = 1;
	else if (*st && *end && is_map_line(line))
		return (1);
	return (0);
}

static void	add_line_to_array(t_map *map, char *line, int *i)
{
	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = '\0';
	map->map[(*i)++] = line;
}

static void	process_map_lines(int fd, t_map *map, int *i)
{
	char	*line;
	int		st;
	int		end;

	st = 0;
	end = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_map_gap(line, &st, &end))
		{
			map->map[*i] = NULL;
			free(line);
			close(fd);
			exit_error(map, "Error\nMap is separated by empty lines");
		}
		if (st && !end)
			add_line_to_array(map, line, i);
		else
			free(line);
	}
}

void	read_map(char *file_path, t_map *map)
{
	int	fd;
	int	i;

	map->height = get_map_height(file_path, map);
	if (map->height == 0)
		exit_error(map, "Error\nNo map found");
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit_error(map, "Error\nMalloc failed");
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_error(map, ERR_FILE);
	i = 0;
	process_map_lines(fd, map, &i);
	close(fd);
	map->map[i] = NULL;
}