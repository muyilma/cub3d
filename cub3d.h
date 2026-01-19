#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

# define ERR_INV "Invalid identifier or line found in file"
# define ERR_USAGE "Usage: ./cub3D <map_path.cub>"
# define ERR_EXT   "Invalid file extension. Must be .cub"
# define ERR_FILE  "Could not open file"

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_y;
    double plane_x;
}       t_player;

typedef struct s_window
{
    void    *no_path;
    void    *so_path;
    void    *we_path;
    void    *ea_path;
    void *init;
    void *win;
    
}   t_window;

typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    int     floor_color;
    int     ceil_color;
    int     p_x;
    int     p_y;
    char    p_dir;
    int     fd;
    t_window window;
    t_player player;
    t_img img;
}   t_map;

void    init_map(t_map *map);
int	close_window(t_map   *data);
t_player  init_player(t_map map);
t_img image_create(t_map data);
void    init_map(t_map *map);
void    check_args(int argc, char **argv);
void    parse_file(char *file_path, t_map *map);
void    exit_error(t_map *map, char *msg);
void    free_map(t_map *map);
int     check_extension(char *file);
int     parse_rgb(char *line, t_map *map);
void    read_map(char *file_path, t_map *map);
void    check_map_validity(t_map *map);
void	free_arr(char **arr);
int     is_map_line(char *line);
int check_disconnected_map(t_map *map, int player_y, int player_x);
t_window open_window(t_map data);

#endif