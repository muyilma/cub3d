#include "cub3d.h"
#include "minilibx-linux/mlx.h"

int	close_window(t_window *maps)
{
	(void)maps;
	// mlx_destroy_window(maps->init, maps->win);
	mlx_destroy_display(maps->init);
	free(maps->init);
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
    t_window   window;

    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);
    check_map_validity(&data);

    printf("-------------------\n");
    window= open_window(window);
    printf("aaaaaaaaaaaaaaaaaaaa\n");
    mlx_hook(window.win, 17, 0, close_window, &data);   
    mlx_loop(window.init);
    // printf("NO: %s\n", data.no_path);
    // printf("SO: %s\n", data.so_path);
    // printf("WE: %s\n", data.we_path);
    // printf("EA: %s\n", data.ea_path);
    // printf("color: %d\n", data.floor_color);
    // printf("color: %d\n", data.ceil_color);

    // printf("\n========= HARITA KONTROL ========\n");
    // printf("Harita Yüksekliği (Height): %d\n", data.height);
    // int     i;
    // if (data.map)
    // {
    //     printf("Harita İçeriği:\n");
    //     i = 0;
    //     while (data.map[i])
    //     {
    //         printf("Satır %d: >%s<\n", i, data.map[i]);
    //         i++;
    //     }
    // }
    // else
    // {
    //     printf("HATA: Harita dizisi oluşturulamadı (NULL)!\n");
    // }
    // printf("=================================\n\n");
    // free_map(&data);
    return (0);
}