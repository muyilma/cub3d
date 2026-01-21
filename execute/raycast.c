/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:39:00 by omgorege          #+#    #+#             */
/*   Updated: 2026/01/21 12:43:11 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)dest = color;
}

double	calc_wall_dist(t_map *d)
{
	if (d->r.side == 0)
		return ((d->r.map_x - d->player.x + (1 - d->r.step_x) / 2)
			/ d->r.ray_x);
	else
		return ((d->r.map_y - d->player.y + (1 - d->r.step_y) / 2)
			/ d->r.ray_y);
}

static void	perform_dda(t_map *d)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->r.side_x < d->r.side_y)
		{
			d->r.side_x += d->r.delta_x;
			d->r.map_x += d->r.step_x;
			d->r.side = 0;
		}
		else
		{
			d->r.side_y += d->r.delta_y;
			d->r.map_y += d->r.step_y;
			d->r.side = 1;
		}
		if (d->map[d->r.map_y][d->r.map_x] == '1')
			hit = 1;
	}
}

static void	init_dda(t_map *d)
{
	d->r.map_x = (int)d->player.x;
	d->r.map_y = (int)d->player.y;
	d->r.delta_x = fabs(1 / d->r.ray_x);
	d->r.delta_y = fabs(1 / d->r.ray_y);
	if (d->r.ray_x < 0)
	{
		d->r.step_x = -1;
		d->r.side_x = (d->player.x - d->r.map_x) * d->r.delta_x;
	}
	else
	{
		d->r.step_x = 1;
		d->r.side_x = (d->r.map_x + 1.0 - d->player.x) * d->r.delta_x;
	}
	if (d->r.ray_y < 0)
	{
		d->r.step_y = -1;
		d->r.side_y = (d->player.y - d->r.map_y) * d->r.delta_y;
	}
	else
	{
		d->r.step_y = 1;
		d->r.side_y = (d->r.map_y + 1.0 - d->player.y) * d->r.delta_y;
	}
}

void	raycast(t_map *d)
{
	int		x;
	int		h;

	x = 0;
	while (x < 1920)
	{
		d->r.camera_x = 2.0 * x / 1920 - 1.0;
		d->r.ray_x = d->player.dir_x + d->player.plane_x * d->r.camera_x;
		d->r.ray_y = d->player.dir_y + d->player.plane_y * d->r.camera_x;
		init_dda(d);
		perform_dda(d);
		d->dist = calc_wall_dist(d);
		h = 1080 / d->dist;
		draw_wall(d, x, -h / 2 + 1080 / 2, h / 2 + 1080 / 2);
		x++;
	}
}
