#include "../cub3d.h"

void    exit_error(char *msg)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}

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
        exit_error(ERR_USAGE);

    if (!check_extension(argv[1]))
        exit_error(ERR_EXT);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error\nSystem");
        exit(1);
    }
    close(fd);
}