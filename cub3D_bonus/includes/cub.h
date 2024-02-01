/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:25 by asalic            #+#    #+#             */
/*   Updated: 2024/02/01 15:05:18 by asalic           ###   ########.fr       */
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
# include <SDL2/SDL.h>
# include <pthread.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <stdbool.h>

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

typedef struct s_parse_ennemy
{
	int		*savex;
	int 	*savey;
	char	*cross_count;
	char	*from_pass;
	char	**map;
	char	dir;
	int		bad_posx[20];
	int		bad_posy[20];
	int		play_posx;
	int		play_posy;
	int 	x;
	int 	y;
	int		i;
	int		ennemies;
	int		crosspass;	
}				t_parse_ennemy;

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

typedef struct s_music
{
	pthread_t			audio;
	int					init;
	SDL_AudioSpec		wav_spec;
	SDL_AudioDeviceID	audio_device;
	Uint32				wav_lenght;
	Uint8				*wav_buffer;
}				t_music;

typedef	struct s_ennemy
{
	float	x;
	float	y;
}	t_ennemy;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	e;
	bool	right;
	bool	left;
}				t_keys;

typedef struct s_mouse
{
	int		mouse_x;
	int		mouse_y;
}				t_mouse;

typedef struct s_menu
{
	void	*img_ptr;
	void	*img_data;
	int		height;
	int		width;
}				t_menu;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bits;
	int			size_line_img;
	int			endian;
	t_data		data;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			floor;
	int			ceiling;
	t_music		sound;
	t_keys		keys;
	t_mouse		win;
	t_ennemy	ennemy;
	t_menu		menu;
	bool		stop;
}	t_window;

/* * * * ERROR HANDLE * * * */
void			error_files(char *cub);
void			handle_error(t_window *window, char *map);
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
char			*go_map(t_parse *put, t_data *data, t_window *window, int tour);

/* * * * MAIN CORE * * * */
void			init_data(t_window *window, char *av);

/* * * * * BONUS * * * * */
void			play_music(void *data);
void			initializer_audio(t_window *window);

int				ennemy_parse(char **map, t_window *window);
void			ennemy_init(t_window *window, t_parse_ennemy *enmy);
void			pos_ennemy_player(t_parse_ennemy *enmy, char **map);
int				ennemy_parse_loop(char **map, t_parse_ennemy *enmy, t_window *window);
int				parsing_ennemy(t_parse_ennemy *enmy, char **map, t_window *window);
void		    go_north(t_parse_ennemy *enmy);
void		    go_west(t_parse_ennemy *enmy);
void		    go_south(t_parse_ennemy *enmy);
void		    go_east(t_parse_ennemy *enmy);
int				go_nowhere(t_parse_ennemy *enmy);
int				choose_path(t_parse_ennemy *enmy);
int				cross_pass(t_parse_ennemy *enmy);
int				is_already_pass(t_parse_ennemy *enmy, int x, int y);
char			**ft_strdup_double(char **str);

int				exit_menu(t_window *window);

#endif