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
    printf("color: %d\n", data.floor_color);
    printf("color: %d\n", data.ceil_color);

    printf("\n========= HARITA KONTROL ========\n");
    printf("Harita Yüksekliği (Height): %d\n", data.height);
    int     i;
    if (data.map)
    {
        printf("Harita İçeriği:\n");
        i = 0;
        while (data.map[i])
        {
            printf("Satır %d: >%s<\n", i, data.map[i]);
            i++;
        }
    }
    else
    {
        printf("HATA: Harita dizisi oluşturulamadı (NULL)!\n");
    }
    printf("=================================\n\n");
    free_map(&data);
    return (0);
}