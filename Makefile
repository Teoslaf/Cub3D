NAME = cub3D
SRCS = main.c read_map.c #draw_map.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft
LIBFT_LIB = libft/libft.a
MLX = mlx
CUB3D_H = cub3D.h
HEADERS = -I $(LIBFT) -I $(MLX)
LIBS = -Lmlx -lmlx_Linux -Imlx -lXext -lX11 -lm

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

%.o: %.c $(CUB3D_H)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)

clean:
	make -C $(LIBFT) clean
	make -C $(MLX) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re