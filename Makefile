#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 10:11:34 by okryzhan          #+#    #+#              #
#    Updated: 2018/10/23 10:11:36 by okryzhan         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf
FLAGS = -Wall -Wextra -Werror
CC = gcc
MLX_HEAD = -I /usr/local/include
MLX_SRCS = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
LIB_HEAD = -I.
LIB_SRCS = -L. -lft
SRCS = main.c \
tests.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(SRCS) $(MLX_SRCS) $(LIB_SRCS)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< $(MLX_HEAD) $(LIB_HEAD)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re