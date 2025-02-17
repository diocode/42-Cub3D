# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 13:27:18 by gabrrodr          #+#    #+#              #
#    Updated: 2025/02/17 14:46:53 by digoncal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all deps clean fclean re

GREEN		= \033[38;5;47m
YELLOW		= \033[38;5;226m
RED			= \033[38;5;196m
CYAN 		= \033[1;36m
RESET 		= \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11

NAME = cub3D

SRC =	src/main.c \
		src/init.c \
		src/free.c \
		src/validations.c \
		src/validations_utils.c \
		src/parse_identifiers.c \
		src/parse_map.c \
		src/parse_map_utils.c \
		src/parse_player.c \
		src/render.c \
		src/raycast.c \
		src/keys.c \
		src/movement.c \
		src/movement_utils.c \
		src/flood_fill.c \
		src/textures.c \
		src/textures_utils.c \

OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: deps $(NAME)
	@echo "[$(GREEN)DONE$(RESET)]:\t\t $(GREEN)cub3d$(RESET)"

deps:
	@echo "[$(CYAN)compiling$(RESET)]:\t $(CYAN)Source files & Libraries$(RESET)"
	@$(MAKE) -C ./libs/libft
	@$(MAKE) -C ./libs/minilibx-linux

$(NAME): $(OBJ) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	@echo "$(YELLOW)Removing objects files$(RESET)"
	@$(MAKE) $@ -C ./libs/libft
	@$(MAKE) $@ -C ./libs/minilibx-linux
	@rm -rf $(OBJ)

fclean: clean
	@echo "$(RED)removing $(NAME) executable$(RESET)"
	@rm -rf $(LIBFT)
	@rm -rf $(NAME)

re: fclean all
