#include "cub3d.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dest;

    if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
        return;
    dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)dest = color;
}

void draw_vertical_line(t_img *img, int x, int start, int end, int color)
{
    int y;

    if (start < 0) start = 0;
    if (end >= 1080) end = 1079;

    y = start;
    while (y <= end)
    {
        my_mlx_pixel_put(img, x, y, color);
        y++;
    }
}
void raycast(t_map *d)
{
    for (int x = 0; x < 1920; x++)
    {
        double camera_x = 2.0 * x / 1920 - 1.0;
        double ray_x = d->player.dir_x + d->player.plane_x * camera_x;
        double ray_y = d->player.dir_y + d->player.plane_y * camera_x;

        int map_x = (int)d->player.x;
        int map_y = (int)d->player.y;

        double delta_x = fabs(1 / ray_x);
        double delta_y = fabs(1 / ray_y);

        int step_x, step_y;
        double side_x, side_y;

        if (ray_x < 0)
        {
            step_x = -1;
            side_x = (d->player.x - map_x) * delta_x;
        }
        else
        {
            step_x = 1;
            side_x = (map_x + 1.0 - d->player.x) * delta_x;
        }

        if (ray_y < 0)
        {
            step_y = -1;
            side_y = (d->player.y - map_y) * delta_y;
        }
        else
        {
            step_y = 1;
            side_y = (map_y + 1.0 - d->player.y) * delta_y;
        }

        int hit = 0, side;
        while (!hit)
        {
            if (side_x < side_y)
            {
                side_x += delta_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_y += delta_y;
                map_y += step_y;
                side = 1;
            }
            if (d->map[map_y][map_x] == '1')
                hit = 1;
        }

        double dist = (side == 0)
            ? (map_x - d->player.x + (1 - step_x) / 2) / ray_x
            : (map_y - d->player.y + (1 - step_y) / 2) / ray_y;

        int h = 1080 / dist;
        draw_vertical_line(&d->img, x,
            -h / 2 + 1080 / 2,
             h / 2 + 1080 / 2,
            side ? 0x00777777 : 0x00FFFFFF);
    }
}
static void player_move(t_map *m, double move_x, double move_y)
{
    double new_x = m->player.x + move_x;
    double new_y = m->player.y + move_y;

    // X ekseni çarpışma
    if (m->map[(int)m->player.y][(int)new_x] != '1')
        m->player.x = new_x;

    // Y ekseni çarpışma
    if (m->map[(int)new_y][(int)m->player.x] != '1')
        m->player.y = new_y;
}
void redraw(t_map *m)
{
    ft_memset(m->img.addr, 0, 1080 * m->img.line_len);
    raycast(m);
    mlx_put_image_to_window(
        m->window.init,
        m->window.win,
        m->img.img,
        0, 0
    );
}

static void rotate_player(t_map *m, double angle)
{
    double old_dir_x = m->player.dir_x;
    double old_plane_x = m->player.plane_x;

    m->player.dir_x = m->player.dir_x * cos(angle)
                    - m->player.dir_y * sin(angle);
    m->player.dir_y = old_dir_x * sin(angle)
                    + m->player.dir_y * cos(angle);

    m->player.plane_x = m->player.plane_x * cos(angle)
                      - m->player.plane_y * sin(angle);
    m->player.plane_y = old_plane_x * sin(angle)
                      + m->player.plane_y * cos(angle);
}

int key_code(int keycode, t_map *m)
{
    double move_speed = 0.1;
    double rot_speed = 0.05;

    if (keycode == 65307)
        close_window(m);

    // W - ileri
    if (keycode == 119 || keycode == 65362)
        player_move(m,
            m->player.dir_x * move_speed,
            m->player.dir_y * move_speed);

    // S - geri
    if (keycode == 115 || keycode == 65364)
        player_move(m,
            -m->player.dir_x * move_speed,
            -m->player.dir_y * move_speed);

    // A - sola strafe
    if (keycode == 97)
        player_move(m,
            -m->player.plane_x * move_speed,
            -m->player.plane_y * move_speed);

    // D - sağa strafe
    if (keycode == 100)
        player_move(m,
            m->player.plane_x * move_speed,
            m->player.plane_y * move_speed);

    // ← sola bak
    if (keycode == 65361)
        rotate_player(m, -rot_speed);

    // → sağa bak
    if (keycode == 65363)
        rotate_player(m, rot_speed);

    redraw(m);
    return (0);
}






int main(int argc, char **argv)
{
    t_map data;

    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);
    check_map_validity(&data);

    data.player = init_player(data);
    data.window = open_window(data);
    data.img = image_create(data);
    raycast(&data);
    mlx_put_image_to_window(data.window.init,data.window.win,data.img.img,0, 0);

    mlx_hook(data.window.win, 17, 0, close_window, &data);
    mlx_hook(data.window.win, 2, (1L << 0), key_code, &data);

    mlx_loop(data.window.init);
    return (0);
}
