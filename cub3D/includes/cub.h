/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:25 by asalic            #+#    #+#             */
/*   Updated: 2024/01/17 18:09:50 by asalic           ###   ########.fr       */
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
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

/* * * * MACROS * * * */

# define NC       "\x1b[0m"
# define RED      "\x1b[31;1m"
# define GREEN    "\x1b[32;1m"
# define YELLOW   "\x1b[33;1m"
# define BLUE     "\x1b[34;1m"
# define MAGENTA  "\x1b[35;1m"
# define CYAN     "\x1b[36;1m"
# define WHITE    "\x1b[37;1m"

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

typedef struct s_ptr
{
	int			width;
	int			height;
	char		**map;
}				t_ptr;

typedef struct s_data
{
	int		x;
	int		y;
	t_ptr	ptr;
}				t_data;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits;
	int		size_line_img;
	int		endian;
	t_data	data;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;
}	t_window;

/* * * * ERROR HANDLE * * * */
void			error_files(char *cub);
void			handle_error(t_window *window, char *map);
void			close_error(t_window *window, char *error);
int				close_wndo(t_window *window);
void			count_error(t_parse *map, int fd);
int				error_cases(void);
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
int				contour_check(t_data *data, char **map);
int				is_contour(int x, int y, char **map, t_data *data);
int				is_mapfile(char *map, t_window *window);
char			*loop_gnl(t_parse *parser);

int				is_good_color(char *comp, char *str, t_window *window);
int				is_good_txture(char *comp, char *str, t_window *window);
char			*convert_rgb_to_hexa(char **rgb);
long			hexa_to_decimal(const char *hexadecimal);

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
int				countmap_y(char	*mappy);
void			countmap_x(char	*mappy, t_window *window);
void			is_in_char_error(t_parse map, int fd, int width);
int				init_count(char *mappy, t_parse *map);
char			*cut_until(char *str, char cut);
char			*cut_from(char *str, char cut);

/* * * * * TAB MAP * * * */
char			**ft_maptab(char *map, t_data *data, t_window *window);
void			print_tab(char **tab);
char			*go_map(t_parse *put, t_data *data, t_window *window, int tour);

/* * * * MAIN CORE * * * */
void			init_data(t_window *window, char *av);

#endif