NAME=cub3d

SRCS= cub3d.c src/init.c src/utils.c

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

.PHONY: all clean fclean re