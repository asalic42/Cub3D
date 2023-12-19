# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 09:08:15 by rciaze            #+#    #+#              #
#    Updated: 2023/12/19 18:14:47 by rciaze           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub_test
MLX_FLAGS 	= -lm -Lmlx -lXext -lX11 -O2
CFLAGS		= -Wall -Wextra -Werror -g3
COMP 		= cc 
CLEANF 		= @(rm -f *.o)
OBJ			= $(addprefix obj/,${SRCS:.c=.o})

# SRCS
SRC			=	src/
LINE		=	line/src/
RECTANGLE	=	rectangle/src/

SRCS 		= \
				$(SRC)main.c \
				$(SRC)utils.c \
				$(SRC)design_p_player.c \
				$(LINE)utils.c \
				$(LINE)draw_lines.c \
				$(LINE)design_p_mlx.c \
				$(RECTANGLE)rectangle.c 
# Couleurs
BOLD		="\033[1m"
RESET		="\033[0m"
LIGHT_GREEN	="\033[92m"
LIGHT_CYAN	="\033[96m"

all : $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo $(BOLD)$(LIGHT_CYAN)Compiling $<... $(RESET)
	@${CC} ${CFLAGS} -c $< -o $@


$(NAME) : $(OBJ)
	@echo $(BOLD)$(LIGHT_GREEN)On compile les librairies$(RESET)

	@make -s -C minilibx-linux
	@echo $(LIGHT_GREEN)	Mlx done.$(RESET)

	@echo $(BOLD)$(LIGHT_CYAN)On move les librairies$(RESET)
	@mv minilibx-linux/libmlx.a .
	@echo $(LIGHT_CYAN)	Mlx done.$(RESET)

	@$(COMP) $(CFLAGS) $(OBJ) libmlx.a $(MLX_FLAGS) -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)Tout est prêt !$(RESET)

clean :
	@make -s clean -C minilibx-linux
	@echo $(LIGHT_GREEN)	Mlx done.$(RESET)
	@rm -rf obj/

	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)

fclean : clean
	
	@echo $(BOLD)$(LIGHT_GREEN)On fclean les librairies$(RESET)
	@make -s clean -C minilibx-linux
	@echo $(LIGHT_GREEN)	Mlx done.$(RESET)

	@rm -f $(NAME)
	@rm -f libmlx.a
	@echo $(BOLD)$(LIGHT_GREEN).a deleted.$(RESET)
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)
	@echo $(BOLD)$(LIGHT_GREEN)Tout est prêt !$(RESET)

re : fclean all


.PHONY : all re clean fclean 