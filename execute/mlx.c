#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"

t_window open_window(t_map data)
{
    t_window window;
    int witdth;
    int height;

    witdth=64;
    height=64;
    window.init=mlx_init();
    window.win =mlx_new_window(window.init,1920,1080,"naber mudur");
    window.no_path=mlx_xpm_file_to_image(window.init,data.no_path,&witdth,&height);
    window.ea_path=mlx_xpm_file_to_image(window.init,data.ea_path,&witdth,&height);
    window.so_path=mlx_xpm_file_to_image(window.init,data.so_path,&witdth,&height);
    window.we_path=mlx_xpm_file_to_image(window.init,data.we_path,&witdth,&height);
    return window;
}

t_player  init_player(t_map map)
{
    map.player.x = map.p_x + 0.5;
    map.player.y = map.p_y + 0.5;

    if (map.p_dir == 'N')
    {
        map.player.dir_x = 0;
        map.player.dir_y = -1;
    }
    else if (map.p_dir == 'S')
    {
        map.player.dir_x = 0;
        map.player.dir_y = 1;
    }
    else if (map.p_dir == 'E')
    {
        map.player.dir_x = 1;
        map.player.dir_y = 0;
    }
    else if (map.p_dir == 'W')
    {
        map.player.dir_x = -1;
        map.player.dir_y = 0;
    }
    map.player.plane_x = -map.player.dir_y * 0.66;//bunları anlamadın
    map.player.plane_y =  map.player.dir_x * 0.66;//bunları anlamadın

    return map.player;
}
