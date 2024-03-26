# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 15:13:34 by nagiorgi          #+#    #+#              #
#    Updated: 2024/03/26 19:11:54 by nagiorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
FLAGS = -Wall -Wextra -I./include -I./minilibx -g
#FLAGS = -Wall -Wextra -I./include -I./minilibx -g
MLXDIR = ./minilibx
LIBFTDIR = ./Libft
INCMLX = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lm
# INCLIBFT = -L$(LIBFTDIR) -lft

OBJDIR = obj/
SRCDIR = src/
SRCS = $(wildcard $(SRCDIR)*.c)
OBJS = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR) > /dev/null 2>&1
	@$(CC) -o $@ $^ $(FLAGS) $(INCMLX)
	@echo "\033[0;32mCompilation réussie ! Le jeu est prêt à être joué.\033[0m"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< $(FLAGS)

.PHONY: clean fclean re

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFTDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "\033[0;32mC'est propre\033[0m"

re: fclean all