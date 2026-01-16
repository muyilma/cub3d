#include "../cub3d.h"

static void	free_pointer(void **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	ptr = NULL;
}

static int **change_to_int(char **map)
{
    int **board;
    int y;
    size_t  len;
    y = 0;
    while (map[y])
        y++;
    board = malloc(sizeof(int *) * (y + 1));
    if (!board)
        return (NULL);
    y = -1;
    while (map[++y])
    {
        len = ft_strlen(map[y]);
        board[y] = ft_calloc(len, sizeof(int));
        if (!board[y])
        {
            while (y--)
                free(board[y]);
            free(board);
            return (NULL);
        }
    }
    board[y] = NULL;
    return (board);
}


static void flood_fill(char **map, int y, int x, int **visited)
{
    if (y < 0 || x < 0 || !map[y])
        return ;
    if (x >= (int)ft_strlen(map[y]))
        return ;
    if (map[y][x] == ' ' || visited[y][x])
        return ;
    visited[y][x] = 1;
    flood_fill(map, y + 1, x, visited);
    flood_fill(map, y - 1, x, visited);
    flood_fill(map, y, x + 1, visited);
    flood_fill(map, y, x - 1, visited);
}

int check_disconnected_map(t_map *map, int player_y, int player_x)
{
    int x;
    int y;
    int **board;
    board = change_to_int(map->map);
    if (!board)
        return (exit_error(map, "Malloc failed"), 1);
    flood_fill(map->map, player_y, player_x, board);
    y = -1;
    while (map->map[++y])
    {
        x = -1;
        while (map->map[y][++x])
        if (ft_strchr("0NSEW1", map->map[y][x]) && !board[y][x])
            return (free_pointer((void **)board),
            exit_error(map, "Map has disconnected Area"), 1);
    }
    return (free_pointer((void **)board), 0);
}

