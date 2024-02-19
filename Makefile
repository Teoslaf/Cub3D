NAME = cub3D
SRCS = main.c read_map/read_map.c move_player3.c read_map/read_map_utils.c move_player_2.c read_map/read_map_utils2.c read_map/read_map_utils3.c read_map/read_map_utils4.c read_map/get_height_utils.c free.c read_map/map_checks.c read_map/map_checks_2.c read_map/map_check_player.c move_player.c read_map/color_texture.c read_map/color_texture_2.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft
LIBFT_LIB = libft/libft.a
MLX = mlx
CUB3D_H = cub3D.h
HEADERS = -I $(LIBFT) -I $(MLX)
LIBS = -Lmlx -lmlx_Linux -Imlx -lXext -lX11 -lm

CC = cc
CFLAGS = -g #-Wall -Wextra -Werror -g

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