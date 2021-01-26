# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:08:06 by odhazzar          #+#    #+#              #
#    Updated: 2020/08/15 11:55:08 by odhazzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

COMP = gcc -Wall -Wextra -Werror
INCLUDES = -Iincludes -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX = mlx/libmlx.a

SOURSES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, obj/%.o, $(SOURSES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MLX) $(OBJECTS)
	$(COMP) $(INCLUDES) $(OBJECTS) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p obj
	$(COMP) -Iincludes -c $< -o $@

clean:
	rm -rf obj
	rm -rf screenshot.bmp

fclean: clean
	rm -rf $(NAME)

re: fclean all