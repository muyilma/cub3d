#include "../cub3d.h"

static int	count_lines(char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

char	**read_whole_file(char *file_path, t_map *map)
{
	int		fd;
	int		i;
	int		line_count;
	char    *gnl_flush;

	line_count = count_lines(file_path);
	if (line_count < 0)
		exit_error(map, ERR_FILE);
	map->file_content = malloc(sizeof(char *) * (line_count + 1));
	if (!map->file_content)
		exit_error(map, "Malloc failed");
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit_error(map, ERR_FILE);
	i = 0;
	while (i < line_count)
		map->file_content[i++] = get_next_line(fd);
	map->file_content[i] = NULL;
	gnl_flush = get_next_line(fd); 
    if (gnl_flush)
	{
        free(gnl_flush);
	}
	close(fd);
	return (map->file_content);
}
