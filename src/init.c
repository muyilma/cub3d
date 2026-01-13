#include "../cub3d.h"

void    init_map(t_map *map)
{
    map->map = NULL;
    map->width = 0;
    map->height = 0;
    map->no_path = NULL;
    map->so_path = NULL;
    map->we_path = NULL;
    map->ea_path = NULL;
    map->floor_color = -1;
    map->ceil_color = -1;   
    map->p_x = -1;
    map->p_y = -1;
    map->p_dir = 0;
}