/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:25 by asalic            #+#    #+#             */
/*   Updated: 2024/01/05 13:52:43 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* * * * INCLUDES * * * */

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "include/main.h"
# include "libft/libft.h"

/* * * * MACROS * * * */

# define NC       "\x1b[0m"
# define RED      "\x1b[31;1m"
# define GREEN    "\x1b[32;1m"
# define YELLOW   "\x1b[33;1m"
# define BLUE     "\x1b[34;1m"
# define MAGENTA  "\x1b[35;1m"
# define CYAN     "\x1b[36;1m"
# define WHITE    "\x1b[37;1m"

// # define WIDTH	1024
// # define HEIGHT	512
// # define PX		64

/* * * * STRUCTURES * * * */
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
}				t_garbage;

typedef struct s_parse
{
	int		x;
	int		y;
	int		count_dir;
	int		fd;
	char	*buffer;
	char	**map;
}				t_parse;

typedef struct s_listmap
{
	int					x;
	int					y;
	int					value;
	struct s_listmap	*next;
	struct s_listmap	*prev;
}				t_listmap;

typedef struct s_ptr
{
	int			width;
	int			height;
	char		**map;
	t_listmap	*list;
}				t_ptr;

typedef struct s_data
{
	int		x;
	int		y;
	t_ptr	ptr;
}				t_data;

/* * * * ERROR HANDLE * * * */
void			error_files(t_window *window, char *cub);
void			handle_error(t_window *window, char *map);
void			close_error(t_window *window, char *error);
int				close_wndo(t_window *window);
void			count_error(t_data *data, t_parse *map, int fd, t_window *window);
int				print_error(char *str);

/* * * * CHECK ERRORS * * * */
int				is_goodext(char *cub);
int				end_filename(char *cub);
int				is_goodfile(char *cub);
int				only_one_thing(char *check_line, int i, int len_player);
int				error_map(char *map);

//Parsing
int				map_up_n_down(char **map, t_data *data);
int				is_zero(int y, char **map, t_data *data);
int				first_line(t_data *data, char **map);
int				main_parse(char **map, t_data *data);
int				is_space(t_data *data, char **map);
int				space_check(t_data *data, char **map);
int				is_contour(int x, int y, char **map, t_data *data);

/* * * * GARBAGE * * * */
t_garbage		*start_garbage(void);
t_garbage_lst	*new_elmt(void *pointer_to);
void			garbage_add(void *pointer);
void			free_garbage(void);
void			add_d_t_garbage(void **double_array, int len);
t_garbage		*get_garbage(void);
void			*ft_malloc(size_t size);
void			malloc_failure(void);

/* * * * UTILS * * * */
int				is_in_char(char c);
int				countmap_y(char	*mappy, t_data *data);
void			countmap_x(char	*mappy, t_data *data);
void			is_in_char_error(t_parse map, t_data *data, int fd, int width);
int				init_count(char *mappy, t_parse *map, t_data *data);

/* * * * * TAB MAP * * * */
char			**ft_maptab(char *map, t_data *data, t_window *window);
void			print_tab(char **tab);
char			*go_map(t_parse *put, t_data *data, t_window *window);

/* * * * LIST MAP * * * */
void			print_list(t_listmap *list);
int				is_good_map(t_listmap *list, char *map);
void			add_arg(t_listmap **list, int x, int y, int value);
t_listmap		*create_arg(int x, int y, int value);

/* * * * MAIN CORE * * * */
void			init_data(t_window *window, char *av);

#endif