#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define ERR_USAGE "Usage: ./cub3D <map_path.cub>"
# define ERR_EXT   "Invalid file extension. Must be .cub"
# define ERR_FILE  "Could not open file"

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
}   t_map;

void    init_map(t_map *map);
void    check_args(int argc, char **argv);
void    exit_error(char *msg);
int     check_extension(char *file);

#endif