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

# define WIDTH	1024
# define HEIGHT	512
# define PX		64

typedef struct s_garbage_lst
{	
	void					*pointer;
	struct s_garbage_lst	*next;	
}t_garbage_lst;

typedef struct s_garbage
{
	int						len_of_lst;
	t_garbage_lst			*head;
	t_garbage_lst			*tail;
}t_garbage;

typedef struct s_parse
{
    int 	x;
    int 	y;
    int 	count_dir;
	int		fd;
	char	*buffer;
	char	**map;
}	t_parse;

typedef struct s_listmap
{
	int 				x;
	int 				y;
	int 				value;
	struct s_listmap* 	next;
	struct s_listmap*	prev;
}	t_listmap;

typedef struct s_ptr
{
	int 		width;
	int 		height;
	void 		*wndo;
	void		*mlx;
	char		**map;
	t_listmap	*list;
}	t_ptr;

typedef struct s_data
{
	int	x;
	int	y;
	t_ptr ptr;
}	t_data;

//Errors handle
int		handle_error(t_parse* parsing, t_listmap *list, char *map);
int		error_map(char *map);
int		only_one_thing(char *check_line, int i, int len_player);
int     is_good_map(t_listmap *list, char *map);
void	close_error(t_data *data);
void	count_error(t_data *data, t_parse *map, int fd);

//Garbage
t_garbage		*start_garbage(void);
t_garbage_lst	*new_elmt(void *pointer_to);
void			garbage_add(void *pointer);
void			free_garbage(void);
void			add_d_t_garbage(void **double_array, int len);
t_garbage		*get_garbage(void);
void			*ft_malloc(size_t size);
void			malloc_failure(void);

//Affichage
void    print_list(t_listmap *list);
char	**ft_maptab(char *map, t_data *data);
void    print_tab(char **tab);

int	main_parse(char **map, t_data *data);

#endif