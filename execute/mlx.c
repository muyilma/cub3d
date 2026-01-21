#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"

void	load_texture(t_map *d, int i, char *path)
{
	d->tex[i].img = mlx_xpm_file_to_image(d->init, path, &d->tex[i].width,
			&d->tex[i].height);
	if (!d->tex[i].img)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putendl_fd(path, 2);
		close_window(d);
	}
	d->tex[i].addr = mlx_get_data_addr(d->tex[i].img, &d->tex[i].bpp,
			&d->tex[i].line_len, &d->tex[i].endian);
	if (!d->tex[i].addr)
	{
		ft_putstr_fd("Error\nFailed to get texture data: ", 2);
		ft_putendl_fd(path, 2);
		close_window(d);
	}
}

void	open_window(t_map *data)
{
	data->init = mlx_init();
	load_texture(data, TEX_NO, data->no_path);
	load_texture(data, TEX_SO, data->so_path);
	load_texture(data, TEX_WE, data->we_path);
	load_texture(data, TEX_EA, data->ea_path);
	data->win = mlx_new_window(data->init, 1920, 1080, "cub3D");
	data->img.img = mlx_new_image(data->init, 1920, 1080);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
}

int	close_window(t_map *data)
{
	if (data->tex[0].img)
		mlx_destroy_image(data->init, data->tex[0].img);
	if (data->tex[1].img)
		mlx_destroy_image(data->init, data->tex[1].img);
	if (data->tex[2].img)
		mlx_destroy_image(data->init, data->tex[2].img);
	if (data->tex[3].img)
		mlx_destroy_image(data->init, data->tex[3].img);
	if (data->img.img)
		mlx_destroy_image(data->init, data->img.img);
	if (data->win)
		mlx_destroy_window(data->init, data->win);
	if (data->init)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	free_map(data);
	exit(0);
}
