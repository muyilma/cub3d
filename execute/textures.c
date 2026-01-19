#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

int	get_wall_dir(t_map *d)
{
	if (d->r.side == 0)
	{
		if (d->r.ray_x > 0)
			return (TEX_WE);
		else
			return (TEX_EA);
	}
	else
	{
		if (d->r.ray_y > 0)
			return (TEX_NO);
		else
			return (TEX_SO);
	}
}

double	get_wall_x(t_map *d, double dist)
{
	double	wall_x;

	if (d->r.side == 0)
		wall_x = d->player.y + dist * d->r.ray_y;
	else
		wall_x = d->player.x + dist * d->r.ray_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_tex_x(t_map *d, int tex_id, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * d->tex[tex_id].width);
	if (d->r.side == 0 && d->r.ray_x > 0)
		tex_x = d->tex[tex_id].width - tex_x - 1;
	if (d->r.side == 1 && d->r.ray_y < 0)
		tex_x = d->tex[tex_id].width - tex_x - 1;
	return (tex_x);
}

int	get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall(t_map *d, int x, int start, int end, double dist)
{
	int		tex_id;
	int		tex_x;
	int		y;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	tex_id = get_wall_dir(d);
	wall_x = get_wall_x(d, dist);
	tex_x = get_tex_x(d, tex_id, wall_x);
	step = 1.0 * d->tex[tex_id].height / (end - start);
	tex_pos = (start - 1080 / 2 + (end - start) / 2) * step;
	if (start < 0)
	{
		tex_pos += (-start) * step;
		start = 0;
	}
	if (end >= 1080)
		end = 1079;
	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos & (d->tex[tex_id].height - 1);
		color = get_tex_color(&d->tex[tex_id], tex_x, tex_y);
		tex_pos += step;
		my_mlx_pixel_put(&d->img, x, y, color);
		y++;
	}
}
