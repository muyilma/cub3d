NAME=cub3D

SRCS= main.c parser/utils.c gnl/get_next_line.c parser/parse.c parser/clean.c parser/parse_utils.c parser/map_read.c parser/read_file.c\
parser/check_map.c parser/flood_fill.c execute/mlx.c init/initalation.c execute/key_code.c execute/raycast.c execute/textures.c

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
	./$(NAME) map/pass/big.cub

leak: all
	valgrind --leak-check=full --show-leak-kinds=all ./cub3D map/pass/big.cub 

.PHONY: all clean fclean re
