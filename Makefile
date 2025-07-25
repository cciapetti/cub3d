# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 16:04:07 by cciapett          #+#    #+#              #
#    Updated: 2025/07/25 17:34:39 by cciapett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d

CC = cc

LIB = -Lminilibx-linux_cub3d -lmlx -lXext -lX11 -lm -Llibft -l:libft.a

CFLAGS = -Wall -Werror -Wextra -g -Iminilibx-linux -Ilibft 

SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
check_direction.c input_file.c inspect.c main.c manager.c messages.c \
parsing.c read_map.c rays.c display.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C minilibx-linux_cub3d
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re