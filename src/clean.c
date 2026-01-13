#include "../cub3d.h"

void    free_map(t_map *map)
{
    if (!map)
        return;
    if (map->no_path)
        free(map->no_path);
    if (map->so_path)
        free(map->so_path);
    if (map->we_path)
        free(map->we_path);
    if (map->ea_path)
        free(map->ea_path);
}

void    exit_error(t_map *map, char *msg)
{
    free_map(map);
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}