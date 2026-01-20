#include "cub3d.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

int main(int argc, char **argv)
{
    t_map data;

    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);
    check_map_validity(&data);
    data.player = init_player(data);
    open_window(&data);
    printf("%d\n", data.floor_color);
    printf("%d\n", data.ceil_color);
    raycast(&data);
    mlx_put_image_to_window(data.init,data.win,data.img.img,0, 0);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 2, (1L << 0), key_code, &data);
    mlx_loop(data.init);
}
