#include "cub3d.h"

int main(int argc, char **argv)
{
    t_map   data;
    check_args(argc, argv);
    init_map(&data);
    parse_file(argv[1], &data);

    printf("NO: %s\n", data.no_path);
    printf("SO: %s\n", data.so_path);
    printf("WE: %s\n", data.we_path);
    printf("EA: %s\n", data.ea_path);

    free_map(&data);
    return (0);
}