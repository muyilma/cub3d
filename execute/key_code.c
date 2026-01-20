#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

static void	player_move(t_map *m, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = m->player.x + move_x;
	new_y = m->player.y + move_y;
	if (m->map[(int)m->player.y][(int)new_x] != '1')
		m->player.x = new_x;
	if (m->map[(int)new_y][(int)m->player.x] != '1')
		m->player.y = new_y;
}

static void	redraw(t_map *m)
{
	raycast(m);
	mlx_put_image_to_window(m->init, m->win, m->img.img, 0, 0);
}

static void	rotate_player(t_map *m, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = m->player.dir_x;
	old_plane_x = m->player.plane_x;
	m->player.dir_x = m->player.dir_x * cos(angle) - m->player.dir_y
		* sin(angle);
	m->player.dir_y = old_dir_x * sin(angle) + m->player.dir_y
		* cos(angle);
	m->player.plane_x = m->player.plane_x * cos(angle) - m->player.plane_y
		* sin(angle);
	m->player.plane_y = old_plane_x * sin(angle) + m->player.plane_y
		* cos(angle);
}

int	key_code(int keycode, t_map *m)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.05;
	if (keycode == 65307)
		close_window(m);
	if (keycode == 119 || keycode == 65362)
		player_move(m, m->player.dir_x * move_speed,
			m->player.dir_y * move_speed);
	if (keycode == 115 || keycode == 65364)
		player_move(m, -m->player.dir_x * move_speed,
			-m->player.dir_y * move_speed);
	if (keycode == 97)
		player_move(m, -m->player.plane_x * move_speed,
			-m->player.plane_y * move_speed);
	if (keycode == 100)
		player_move(m, m->player.plane_x * move_speed,
			m->player.plane_y * move_speed);
	if (keycode == 65361)
		rotate_player(m, -rot_speed);
	if (keycode == 65363)
		rotate_player(m, rot_speed);
	redraw(m);
	return (0);
}
