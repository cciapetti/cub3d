# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cciapett <cciapett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 16:04:07 by cciapett          #+#    #+#              #
#    Updated: 2025/09/11 14:28:56 by cciapett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d

CC = cc

LIB = -Lminilibx-linux_cub3d -lmlx -lXext -lX11 -lm -Llibft -l:libft.a

CFLAGS = -Wall -Werror -Wextra -g -Iminilibx-linux -Ilibft 

SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
parsing/check_direction.c parsing/clean_parsing.c \
parsing/input_file.c parsing/inspect.c \
parsing/inspect2.c parsing/line.c parsing/messages.c \
parsing/parsing_map.c parsing/parsing_utils.c parsing/parsing.c \
main.c read_map.c rays.c display.c computation.c moves.c color.c

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

norminette: 
	norminette $(SRCS)

.PHONY: all clean fclean re
