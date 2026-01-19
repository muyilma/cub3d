#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"



void open_window(t_map *data)
{

    data->init=mlx_init();
    data->win =mlx_new_window(data->init,1920,1080,"naber mudur");
    
}

int	close_window(t_map   *data)
{
    mlx_destroy_image(data->init, data->tex[0].img);
    mlx_destroy_image(data->init, data->tex[1].img);
    mlx_destroy_image(data->init, data->tex[2].img);
    mlx_destroy_image(data->init, data->tex[3].img);

    mlx_destroy_image(data->init,data->img.img);
	mlx_destroy_window(data->init, data->win);
	mlx_destroy_display(data->init);

	free(data->init);
    
    free_map(data);
	exit(0);
}
