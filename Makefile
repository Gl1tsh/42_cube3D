NAME = cub3D
CC = gcc
FLAGS = -Wall -Werror -Wextra -I./include -I./minilibx -I./libft -g
#FLAGS = -Wall -Wextra -I./include -I./minilibx -g
MLXDIR = ./minilibx
LIBFTDIR = ./Libft
INCMLX = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lm
# INCLIBFT = -L$(LIBFTDIR) -lft
CRED = \033[1;31m
CGRN = \033[1;32m
CYEL = \033[1;33m
RSET = \033[0m
CVIO = \033[1;35m
BUILDDIR = build/

SRCS = src/map_checking.c src/anim.c src/draw_surface.c src/draw.c src/free.c src/game.c src/image.c src/main.c src/map.c src/menu.c src/mini_map.c src/parsing.c src/player.c src/utils.c
OBJS = $(patsubst src/%.c,$(BUILDDIR)%.o,$(SRCS))

HAS_WARNINGS :=

# Include the dependency files
-include $(OBJS:.o=.d)

# Règle pour créer les fichiers objets
${BUILDDIR}%.o: src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@ 2> temp_warnings && printf "│ Compiling ${CGRN}$< = OK${RSET}\n" || (printf "│ Compiling ${CRED}$< = failed${RSET}\n" && cat temp_warnings && printf "├──────────\n├─>>> ${CRED}cube3d compiling failed!${RSET}\n└──────────\n" && exit 1)
	@if grep -q "warning" temp_warnings; then \
        printf "│ Compiling ${CVIO}$< = warnings${RSET}\n"; \
        echo 1 > has_warnings; \
    else \
        printf ""; \
    fi
	@cat temp_warnings
	@rm -f temp_warnings

# Règle par défaut
all: ${NAME}

${LIBFT}:
	@if [ ! -f libft/libft.a ]; then \
		printf "├──────────\n"	; \
		printf "│ Compiling ${CGRN}libft${RSET}...\n"; \
		${MAKE} -s -C libft all; \
		printf "└──────────\n"; \
	fi

# Règle pour créer l'exécutable
${NAME}: ${LIBFT} ${MLXDIR} ${OBJS}
	@make -C $(LIBFTDIR)
	@make -C $(MLXDIR)
	@${CC} -o ${NAME} ${OBJS} -Llibft -lft ${FLAGS} ${INCMLX} 
	@printf "├──────────\n"
	@if [ -f has_warnings ]; then \
		printf "├─>>>${CGRN} cube3d compiled ${CVIO}but with warnings!${RSET}\n"; \
	else \
		printf "├─>>>${CGRN} cube3d compiled!${RSET}\n"; \
	fi
	@printf "└──────────\n"
	@rm -f has_warnings

# Règle pour nettoyer les fichiers objets
clean:
	@printf "┌──────────\n"
	@printf "│  Removing ${CRED}${BUILDDIR}${RSET} for ${CYEL}${NAME}${RSET} : ${CGRN}OK${RSET}\n"
	@find ${BUILDDIR} -type f -delete
	@printf "│  Removing ${CRED}Libft/${RSET} for ${CYEL}${NAME}${RSET} : ${CGRN}OK${RSET}\n"
	@${MAKE} -C libft clean
	@printf "│  Removing ${CRED}tmp error files${RSET} for ${CYEL}${NAME}${RSET} : ${CGRN}OK${RSET}\n"
	@rm -f *~ \#*\# .\#*
	@printf "├──────────\n"	;
	@printf "├─>>> Removing status : ${CGRN}Done ${RSET}\n"
	@printf "└──────────\n"

# Règle pour nettoyer les fichiers objets et l'exécutable
fclean: clean
	@if [ -e "./${NAME}" ]; then \
		rm -f ${NAME}; \
	fi
	@${MAKE} -C libft fclean
	@rm -f temp.log
	@printf "│  Removing ${CYEL}${NAME}${RSET} : ${CGRN}OK${RSET}\n└──────────\n";

# Règle pour recompiler les fichiers objets et l'exécutable
re:
	@printf "\n┌──────────\n│ Cleaning and ${CGRN}recompiling${RSET}...\n"
	@${MAKE} fclean
	@${MAKE} all

error:
	@printf "${CVIO}├─>>> Warnings:${RSET}\n"
	@printf "${CGRN}No warnings were generated during the last build.${RSET}\n"

.PHONY: all clean fclean re
