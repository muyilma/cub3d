#include "../cub3d.h"

static char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

static void	parse_path(char *line, t_map *map, char **path_ptr)
{
	char	*trimmed;

	if (*path_ptr != NULL)
		exit_error(map, "Error\nDuplicate texture identifier");
	
	line += 2;
	line = skip_spaces(line);
	trimmed = ft_strtrim(line, " \n");
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		if (trimmed)
			free(trimmed);
		exit_error(map, "Error\nInvalid texture path");
	}
	*path_ptr = trimmed;
}

static void	parse_color_line(char *line, t_map *map, int *color_ptr)
{
	char	*ptr;

	if (*color_ptr != -1)
		exit_error(map, "Error\nDuplicate color identifier");
	
	ptr = line + 1;
	ptr = skip_spaces(ptr);

	if (!*ptr)
		exit_error(map, "Error\nMissing color values");
	*color_ptr = parse_rgb(ptr, map);
}

static int	parse_line(char *line, t_map *map)
{
	char	*ptr;

	ptr = skip_spaces(line);
	if (!*ptr || *ptr == '\n')
		return (0);
	if (ft_strncmp(ptr, "NO", 2) == 0)
		parse_path(ptr, map, &map->no_path);
	else if (ft_strncmp(ptr, "SO", 2) == 0)
		parse_path(ptr, map, &map->so_path);
	else if (ft_strncmp(ptr, "WE", 2) == 0)
		parse_path(ptr, map, &map->we_path);
	else if (ft_strncmp(ptr, "EA", 2) == 0)
		parse_path(ptr, map, &map->ea_path);
	else if (ft_strncmp(ptr, "F", 1) == 0)
		parse_color_line(ptr, map, &map->floor_color);
	else if (ft_strncmp(ptr, "C", 1) == 0)
		parse_color_line(ptr, map, &map->ceil_color);
	else if (*ptr == '1' || *ptr == '0')
		return (1);
	else
	{
		free(line);
		exit_error(map, "Error\nInvalid identifier");
	}
	return (0);
}

void	parse_file(char *file_path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_error(map, ERR_FILE);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(line, map))
		{
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
		|| map->floor_color == -1 || map->ceil_color == -1)
	{
		exit_error(map, "Missing texture or color identifiers");
	}
	read_map(file_path, map);
}
