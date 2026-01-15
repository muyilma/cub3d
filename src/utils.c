#include "../cub3d.h"

int     check_extension(char *file)
{
    size_t  len;

    len = ft_strlen(file);
    if (len < 4)
        return (0);
    if (ft_strncmp(file + len - 4, ".cub", 4) == 0)
        return (1);
    return (0);
}

void    check_args(int argc, char **argv)
{
    int fd;

    if (argc != 2)
        exit_error(NULL, ERR_USAGE);

    if (!check_extension(argv[1]))
        exit_error(NULL, ERR_EXT);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error\nSystem");
        exit(1);
    }
    close(fd);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}