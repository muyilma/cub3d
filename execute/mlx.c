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

int	close_window(t_map   *data)
{
    mlx_destroy_image(data->window.init,data->img.img);
	mlx_destroy_window(data->window.init, data->window.win);
	mlx_destroy_display(data->window.init);
	free(data->window.init);
    
    free_map(data);
	exit(0);
}
