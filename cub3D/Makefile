# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asalic <asalic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/21 18:01:21 by asalic            #+#    #+#              #
#    Updated: 2024/01/23 18:31:11 by asalic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3D
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
LIBS		= -Lminilibx-linux -lmlx -Llibft -lft -lXext -lX11 -lm -O2
PATH_MLX	= minilibx-linux/libmlx.a
PATH_LIBFT	= libft/libft.a
INCLUDES	= minilibx-linux/mlx.h libft/libft.h includes/main.h includes/cub.h includes/forme.h includes/basique_mlx_needed.h

SRCS_DIR = src src/design_p src/map-parsing src/utils src/formes
SRCS	:= $(foreach dir,$(SRCS_DIR),$(wildcard $(dir)/*.c)) $(SRCS)
OBJ_DIR	 = obj
OBJ		 = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

# Couleurs
BOLD		= "\033[1m"
RESET		= "\033[0m"
LIGHT_GREEN	= "\033[92m"
LIGHT_CYAN	= "\033[96m"

all		: $(PATH_MLX) $(PATH_LIBFT) $(NAME) $(INCLUDES)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@
	@echo $(BOLD)$(LIGHT_CYAN)"Generating obj...\n"$(RESET)

$(NAME)	: $(OBJ)
	@$(CC) $(CFLAGS) -Iincludes $(OBJ) -o $(NAME) $(LIBS)
	@echo $(BOLD)$(LIGHT_GREEN)"Compilation Done !\n"$(RESET)

$(PATH_MLX) :
	@make -s -C minilibx-linux/	

$(PATH_LIBFT) :
	@make -s -C libft
clean	:
	@make -s clean -C libft
	@make -s clean -C minilibx-linux/
	@rm -rf $(OBJ) $(OBJ_DIR)
	@echo $(BOLD)$(LIGHT_GREEN)"Clean Done !\n"$(RESET)

fclean	: clean
	@make -s 	fclean -C libft
	@rm -rf $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)"FClean Done !\n"$(RESET)

re : fclean
	@make -s all

.PHONY : all re clean fclean 