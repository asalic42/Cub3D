# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asalic <asalic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 17:02:35 by asalic            #+#    #+#              #
#    Updated: 2024/01/16 18:12:19 by asalic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= audio
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
LIBS		= -Lminilibx-linux -lmlx -lXext -lSDL2 -lX11 -lm -O2
PATH_MLX	= minilibx-linux/libmlx.a
INCLUDES	= minilibx-linux/mlx.h main.h

SRCS	:= $(wildcard *.c)
OBJ_DIR	 = obj
OBJ		 = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Couleurs
BOLD		= "\033[1m"
RESET		= "\033[0m"
LIGHT_GREEN	= "\033[92m"
LIGHT_CYAN	= "\033[96m"

all		: $(PATH_MLX) $(NAME) $(INCLUDES)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@
	@echo $(BOLD)$(LIGHT_CYAN)"Generating obj...\n"$(RESET)

$(NAME)	: $(OBJ)
	@$(CC) $(CFLAGS) -Iincludes $(OBJ) -o $(NAME) $(LIBS)
	@echo $(BOLD)$(LIGHT_GREEN)"Compilation Done !\n"$(RESET)

$(PATH_MLX) :
	@make -s -C minilibx-linux/	

clean	:
	@make -s clean -C minilibx-linux/
	@rm -rf $(OBJ) $(OBJ_DIR)
	@echo $(BOLD)$(LIGHT_GREEN)"Clean Done !\n"$(RESET)

fclean	: clean
	@rm -rf $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)"FClean Done !\n"$(RESET)

re : fclean
	@make -s all

.PHONY : all re clean fclean 