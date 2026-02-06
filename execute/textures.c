/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:39:03 by omgorege          #+#    #+#             */
/*   Updated: 2026/01/21 12:42:38 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

int	get_wall_dir(t_map *d)
{
	if (d->r.side == 0)
	{
		if (d->r.ray_x > 0)
			return (TEX_EA);
		else
			return (TEX_WE);
	}
	else
	{
		if (d->r.ray_y > 0)
			return (TEX_SO);
		else
			return (TEX_NO);
	}
}

double	get_wall_x(t_map *d, int tex_id, double dist)
{
	double	wall_x;
	int		tex_x;

	if (d->r.side == 0)
		wall_x = d->player.y + dist * d->r.ray_y;
	else
		wall_x = d->player.x + dist * d->r.ray_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * d->tex[tex_id].width);
	if (d->r.side == 0 && d->r.ray_x < 0)
		tex_x = d->tex[tex_id].width - tex_x - 1;
	if (d->r.side == 1 && d->r.ray_y > 0)
		tex_x = d->tex[tex_id].width - tex_x - 1;
	return (tex_x);
}

int	get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	clamp_wall_bounds(int *start, int *end, double step, double *tex_pos)
{
	if (*start < 0)
	{
		*tex_pos += (-*start) * step;
		*start = 0;
	}
	if (*end >= 1080)
		*end = 1079;
}

void	draw_wall(t_map *d, int x, int start, int end)
{
	int		y;
	double	step;
	double	tex_pos;

	d->t_id = get_wall_dir(d);
	d->t_x = get_wall_x(d, d->t_id, d->dist);
	step = 1.0 * d->tex[d->t_id].height / (end - start);
	tex_pos = 0.0;
	clamp_wall_bounds(&start, &end, step, &tex_pos);
	y = 0;
	while (y < start)
		my_mlx_pixel_put(&d->img, x, y++, d->ceil_color);
	y = start - 1;
	while (++y <= end)
	{
		d->t_y = (int)tex_pos % d->tex[d->t_id].height;
		tex_pos += step;
		my_mlx_pixel_put(&d->img, x, y, get_tex_color(&d->tex[d->t_id], d->t_x,
				d->t_y));
	}
	while (y < 1080)
		my_mlx_pixel_put(&d->img, x, y++, d->floor_color);
}
