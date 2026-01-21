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
	int		fd;

	if (*path_ptr != NULL)
		exit_error(map, "Duplicate texture identifier");
	line += 2;
	line = skip_spaces(line);
	trimmed = ft_strtrim(line, " \n\t");
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		if (trimmed)
			free(trimmed);
		exit_error(map, "Invalid texture path");
	}
	*path_ptr = trimmed;
	fd = open(*path_ptr, O_RDONLY);
	if (fd < 0 || (!check_extension(*path_ptr, ".xpm")))
	{
		exit_error(map, ERR_FILE);
	}
	close(fd);
}

static void	parse_color_line(char *line, t_map *map, int *color_ptr)
{
	char	*ptr;

	if (*color_ptr != -1)
		exit_error(map, "Duplicate color identifier");
	ptr = line + 1;
	ptr = skip_spaces(ptr);
	if (!*ptr)
		exit_error(map, "Missing color values");
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
		exit_error(map, "Invalid identifier");
	}
	return (0);
}

void	parse_file(char *file_path, t_map *map)
{
	int	i;

	read_whole_file(file_path, map);
	i = 0;
	while (map->file_content[i])
	{
		if (parse_line(map->file_content[i], map))
			break ;
		i++;
	}
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
		|| map->floor_color == -1 || map->ceil_color == -1)
	{
		exit_error(map, "Missing texture or color identifiers");
	}
	process_map_content(map, i);
}
