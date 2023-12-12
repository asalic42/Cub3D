NAME 		= cub3D
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBS		= -Lminilibx-linux -lmlx -Llibft -lft -lGL -lXext -lX11 -lm
PATH_MLX	= minilibx-linux/libmlx.a
PATH_LIBFT	= libft/libft.a
INCLUDES	= cub.h minilibx-linux/mlx.h libft/libft.h

SRCS	= main.c
OBJ_DIR	= obj
OBJ		= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

all		: $(PATH_MLX) $(PATH_LIBFT) $(NAME) $(INCLUDES)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Generating obj...\n"

$(NAME)	: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@echo "Compilation Done !\n"

$(PATH_MLX) :
	@make -s -C minilibx-linux

$(PATH_LIBFT) :
	@make -s -C libft
clean	:
	@make -s clean -C minilibx-linux
	@make -s clean -C libft
	@rm -rf $(OBJ) $(OBJ_DIR)
	@echo "Clean Done !\n"

fclean	: clean
	@make -s fclean -C libft
	@rm -rf $(NAME)
	@echo "FClean Done !\n"

re : fclean
	@make -s all

