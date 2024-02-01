/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:34:24 by asalic            #+#    #+#             */
/*   Updated: 2024/02/01 20:20:00 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "forme.h"
# include "cub.h"
# include <X11/X.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# define PI 3.1415926535
# define PI2 1.57079632675
# define PI3 4.71238898025
# define DR 0.0006363179
# define R_FOV 1.22173
# define NB_OF_STRIPES 1920
# define WIDTH 1920
# define HEIGHT 1010

extern int			compteur;
extern clock_t		all_start;
extern clock_t		all_end;


typedef struct s_music
{
	pthread_t			audio;
	int					init;
	SDL_AudioSpec		wav_spec;
	SDL_AudioDeviceID	audio_device;
	Uint32				wav_lenght;
	Uint8				*wav_buffer;
}				t_music;

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

typedef struct s_ptr
{
	int			width;
	int			height;
	char		**map;
}				t_ptr;

typedef struct s_player_pos
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	a;
}	t_player_pos;

typedef struct s_map
{
	int		mp;
	int		mx;
	int		my;
	int		x;
	int		y;
	int		*map;
}	t_map;

typedef struct s_texture_details
{
	int				width;
	int				height;
	void			*xpm;
	void			*xpm_data;
}	t_texture_details;

typedef struct s_textures_path
{
	t_texture_details	xpm1;
	t_texture_details	xpm2;
	t_texture_details	xpm3;
	t_texture_details	xpm4;
	t_texture_details	xpm_door;
	t_texture_details	xpm_ennemy;
	t_texture_details	xpm_ennemy_dead;
	t_texture_details	xpm_weapon;
	t_texture_details	xpm_weapon_firing;
}	t_textures_path;

typedef struct s_stuff_for_ray_casting
{
	int				r;
	int				mx;
	int				my;
	int				mp;
	int				dof;
	float			rx;
	float			ry;
	float			ra;
	float			vertical_xo;
	float			vertical_yo;
	float			horizontal_xo;
	float			horizontal_yo;
	float			xo;
	float			yo;
	float			dist_h;
	float			dist_t;
	float			hx;	
	float			hy;
	float			a_tan;
	float			dist_v;
	float			vx;
	float			vy;
	float			n_tan;
	float			ca;
	float			original_line_h;
	float			line_h;
	float			line_off;
	t_line			line;
	unsigned int	color;
	t_player_pos	*player;
	t_map			*map;
	float			lenght_tab[1920];
}	t_stuff_for_ray_casting;

typedef struct s_put_texture_to_img_data
{
	int			y;
	void		*img_data;
	t_tmp_pixel	tmp_p;
	char		*pixel;
	int			current_x;
	char		*value;
	float		texture_position;
	float		texture_step;
	int			tex_y;
	int			tex_x;
}	t_put_texture_to_img_data;

typedef struct s_minimap
{
	int		j;
	int		i;
	int		cptr_y;
	int		cptr_x;
	t_line	line;
	int		my;
}	t_minimap;

typedef struct s_data
{
	int		x;
	int		y;
	t_ptr	ptr;
}				t_data;

typedef	struct s_print_ennemy
{
	float		x_vector;
	float		y_vector;
	float		lenght;
	float		target_angle;
	float		relative_angle;
	int			save;
	float		dist;
	float		texture_step;
	int			start_x;
	int			end_x;
	float		position_x;
	int			end_y, y;
	int			tex_x;
	int			tex_y;
	float		texture_position;
	unsigned	*value;
	char		*pixel;
	int			i;
	int			width;
}	t_print_ennemy;

typedef	struct s_fps
{
	clock_t	start;
	clock_t	end;
	int		t_compteur;
	int		compteur;
	char	*str;
}	t_fps;

typedef	struct s_ennemy
{
	float				x;
	float				y;
	float				dist_to_player;
	t_texture_details	*tex;
}	t_ennemy;

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
	t_ennemy	ennemies[20];
	int			ennemies_count;
	t_menu		menu;
	bool		stop;
	bool		anim_bool;
}	t_window;

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



void			shot_fired(t_window *window);
void			print_weapon(t_window *window, t_texture_details *xpm, int j);
int				comparator(const void* p, const void* p2);
int				size_of_array(t_window *window);
t_fps			*get_fps_instance(void);
float			normalize_angle(float angle);
void			ennemy(t_textures_path *textures, t_stuff_for_ray_casting *all_stuff, t_window *window);
int				handle_no_event(void *window);
void			draw_map(t_window *window, t_player_pos	*player, t_map *map);
void			colision(t_player_pos *player, float dx, float dy);
void			wich_texture(int comp, t_textures_path *textures,
					t_window *window, t_stuff_for_ray_casting *all_stuff);
void			texture_to_screen(t_stuff_for_ray_casting *all_stuff,
					t_texture_details *xpm, void *img_data, int comp);
void			calculations(t_put_texture_to_img_data *variables,
					t_stuff_for_ray_casting *all_stuff, int *end_y,
					t_texture_details *xpm);
void			find_player(t_map *map, t_player_pos *player, char **char_map);
void			init_textures(t_window *window, char *door, char *ennemy);
int				move_player(t_window *window);
void			rotation(t_player_pos *player, t_window	*window);
void			move_up(t_player_pos *player, t_window *window);
void			move_down(t_player_pos *player, t_window *window);
void			move_right_left(t_player_pos *player, t_window *window);
int				key_release(int keycode, t_window *window);
int				move_player(t_window *window);
t_textures_path	*get_textures_instance(void);
int				key_press(int keycode, t_window *window);
int				handle_no_event(void *window);
int				create_window(t_window *window);
int				*simple_tab_int(char **char_map, t_window *window);
int				destroy_window(t_window *window);
void			draw_player(t_window *window);
t_map			*get_map_instance(void);
t_player_pos	*get_player_instance(void);
void			up_or_down(t_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			find_closest_horizontal_intersection(
					t_stuff_for_ray_casting *all_stuff, t_window *window);
void			left_or_right(t_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			find_closest_vertical_intersection(
					t_stuff_for_ray_casting *all_stuff, t_window *window);
float			distance(float ax, float ay, float bx, float by);
int				comp_distance(t_stuff_for_ray_casting *all_stuff);
float			distance(float ax, float ay, float bx, float by);
void			init_ray(t_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			init_distances(t_stuff_for_ray_casting *all_stuff);
void			calculate_line_height(t_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			increment_angle(t_stuff_for_ray_casting *all_stuff);
void			is_player_out_of_bouds(t_player_pos *player, t_window *window);

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
