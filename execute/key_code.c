#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

static void	player_move(t_map *m, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = m->player.x + move_x;
	new_y = m->player.y + move_y;
	if (m->map[(int)m->player.y][(int)(new_x + 0.2 * (move_x > 0) 
		- 0.2 * (move_x < 0))] != '1')
		m->player.x = new_x;
	if (m->map[(int)(new_y + 0.2 * (move_y > 0) 
		- 0.2 * (move_y < 0))][(int)m->player.x] != '1')
		m->player.y = new_y;
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

int	key_press(int keycode, t_map *m)
{
	if (keycode == 65307)
		close_window(m);
	if (keycode == 119)
		m->keys.w = 1;
	if (keycode == 115)
		m->keys.s = 1;
	if (keycode == 97)
		m->keys.a = 1;
	if (keycode == 100)
		m->keys.d = 1;
	if (keycode == 65361)
		m->keys.left = 1;
	if (keycode == 65363)
		m->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_map *m)
{
	if (keycode == 119)
		m->keys.w = 0;
	if (keycode == 115)
		m->keys.s = 0;
	if (keycode == 97)
		m->keys.a = 0;
	if (keycode == 100)
		m->keys.d = 0;
	if (keycode == 65361)
		m->keys.left = 0;
	if (keycode == 65363)
		m->keys.right = 0;
	return (0);
}

static void	handle_movement(t_map *m, double ms, double rs)
{
	if (m->keys.w)
		player_move(m, m->player.dir_x * ms, m->player.dir_y * ms);
	if (m->keys.s)
		player_move(m, -m->player.dir_x * ms, -m->player.dir_y * ms);
	if (m->keys.a)
		player_move(m, -m->player.plane_x * ms, -m->player.plane_y * ms);
	if (m->keys.d)
		player_move(m, m->player.plane_x * ms, m->player.plane_y * ms);
	if (m->keys.left)
		rotate_player(m, -rs);
	if (m->keys.right)
		rotate_player(m, rs);
}

int	game_loop(t_map *m)
{
	handle_movement(m, 0.05, 0.03);
	raycast(m);
	mlx_put_image_to_window(m->init, m->win, m->img.img, 0, 0);
	return (0);
}
