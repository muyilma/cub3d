#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"

t_window open_window()
{
    t_window window;

    window.init=mlx_init();
    if (!window.init)
    {
        write(2, "mlx_init failed\n", 16);
        exit(1);
    }   
    window.win =mlx_new_window(window.init,1920,1080,"naber mudur");

    return window;
}