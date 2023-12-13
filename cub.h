#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "libft/libft.h"

# define NC       "\x1b[0m"
# define RED      "\x1b[31;1m"
# define GREEN    "\x1b[32;1m"
# define YELLOW   "\x1b[33;1m"
# define BLUE     "\x1b[34;1m"
# define MAGENTA  "\x1b[35;1m"
# define CYAN     "\x1b[36;1m"
# define WHITE    "\x1b[37;1m"

typedef struct s_parse
{
    int x;
    int y;
    int count_dir;
} t_parse;

//Errors handle
int		handle_error(t_parse* parsing, char *map);
int		error_map(int fd);
int		only_one_thing(char *check_line, int i, int len_player);

#endif