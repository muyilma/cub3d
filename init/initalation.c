#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"

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

t_img image_create(t_map data)
{
    t_img new_image;

    new_image.img  = mlx_new_image(data.window.init, 1920, 1080);
    new_image.addr = mlx_get_data_addr(new_image.img,&new_image.bpp,&new_image.line_len,&new_image.endian);
    return new_image;
}