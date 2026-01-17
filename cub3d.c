#include "cub3d.h"
#include "minilibx-linux/mlx.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}


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
	map->fd =-1;
}

int main(int argc, char **argv)
{
    t_map data;
    int x;
    int y;

    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);
    check_map_validity(&data);

    data.window = open_window(data);
    data.player = init_player(data);

    /* IMAGE OLUŞTUR */
    data.img.img = mlx_new_image(data.window.init, 1920, 1080);
    data.img.addr = mlx_get_data_addr(
        data.img.img,
        &data.img.bpp,
        &data.img.line_len,
        &data.img.endian
    );

    /* TEST: EKRANI GRİ BOYA */
    y = 0;
    while (y < 1080)
    {
        x = 0;
        while (x < 1920)
        {
            my_mlx_pixel_put(&data.img, x, y, 0xf3245f);
            x++;
        }
        y++;
    }

    mlx_put_image_to_window(
        data.window.init,
        data.window.win,
        data.img.img,
        0, 0
    );

    mlx_hook(data.window.win, 17, 0, close_window, &data);
    mlx_loop(data.window.init);

    return (0);
}
