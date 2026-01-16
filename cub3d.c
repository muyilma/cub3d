#include "cub3d.h"
#include "minilibx-linux/mlx.h"

int	close_window(t_map   *data)
{
	mlx_destroy_window(data->window.init, data->window.win);
	mlx_destroy_display(data->window.init);
	free(data->window.init);
    free_map(data);
	exit(0);
}

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

int main(int argc, char **argv)
{
    t_map   data;

    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);
    check_map_validity(&data);

    data.window = open_window(data);
    mlx_hook(data.window.win, 17, 0, close_window, &data);   
    mlx_loop(data.window.init);
     free_map(&data);
    return (0);
}