#include "cub3d.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

void    load_texture(t_map *d, int i, char *path)
{
    d->tex[i].img = mlx_xpm_file_to_image(d->init,path,&d->tex[i].width,&d->tex[i].height);
    d->tex[i].addr = mlx_get_data_addr(d->tex[i].img,&d->tex[i].bpp,&d->tex[i].line_len,&d->tex[i].endian);
}

void image_create(t_map *data)
{
    data->img.img  = mlx_new_image(data->init, 1920, 1080);
    data->img.addr = mlx_get_data_addr(data->img.img,&data->img.bpp,&data->img.line_len,&data->img.endian);
}

int main(int argc, char **argv)
{
    t_map data;

    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);
    check_map_validity(&data);

    data.player = init_player(data);
    open_window(&data);
    image_create(&data);
    load_texture(&data, TEX_NO, data.no_path);
    load_texture(&data, TEX_SO, data.so_path);
    load_texture(&data, TEX_WE, data.we_path);
    load_texture(&data, TEX_EA, data.ea_path);
    raycast(&data);
    mlx_put_image_to_window(data.init,data.win,data.img.img,0, 0);

    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 2, (1L << 0), key_code, &data);

    mlx_loop(data.init);
    return (0);
}
