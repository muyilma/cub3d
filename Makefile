NAME=cub3d

SRCS= cub3d.c src/utils.c gnl/get_next_line.c src/parse.c src/clean.c src/parse_utils.c src/map_read.c src/check_map.c src/flood_fill.c execute/mlx.c

CFLAGS=-Wall -Wextra -Werror -g

LIBFT=libft/libft.a

MLX_LIB=minilibx-linux/libmlx.a

MLX_FLAGS=-L/usr/X11R6/lib -lXext -lX11 -lm -lbsd

all: $(NAME)

$(NAME): $(SRCS) 
	make -C ./libft -s
	make -C ./minilibx-linux -s
	cc  -o  $(NAME) $(CFLAGS) $(SRCS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS)

clean:
	make clean -C ./libft -s
	make clean -C ./minilibx-linux -s

fclean: clean
	make fclean -C ./libft -s
	rm -rf $(NAME)
	rm -rf $(MLX_LIB)

re: fclean all

run: all
	clear
	./$(NAME) map/map.cub

leak: all
	valgrind --leak-check=full --show-leak-kinds=all ./cub3d map/map.cub 

.PHONY: all clean fclean re
