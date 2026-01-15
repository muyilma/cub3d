NAME=cub3d

SRCS= cub3d.c src/init.c src/utils.c gnl/get_next_line.c src/parse.c src/clean.c src/parse_utils.c src/map_read.c src/check_map.c

CFLAGS=-Wall -Wextra -Werror 

LIBFT=libft/libft.a

all: $(NAME)

$(NAME): $(SRCS) 
	make -C ./libft -s
	cc  -o  $(NAME) $(CFLAGS) $(SRCS) $(LIBFT)

clean:
	make clean -C ./libft -s

fclean: clean
	make fclean -C ./libft -s
	rm -rf $(NAME)

re: fclean all

run: all
	./$(NAME) map/map.cub

.PHONY: all clean fclean re
