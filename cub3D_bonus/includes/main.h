/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:34:24 by asalic            #+#    #+#             */
/*   Updated: 2024/01/29 14:19:07 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minilibx-linux/mlx.h"
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
# define PI 3.1415926535
# define PI2 1.57079632675
# define PI3 4.71238898025
# define DR 0.0006363179

extern int			compteur;
extern clock_t		all_start;
extern clock_t		all_end;

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
	int				lenght_tab[960];
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

typedef	struct s_print_ennemy
{
	float	x_vector;
	float	y_vector;
	float	lenght;
	float	target_angle;
	float	relative_angle;
	int		save;
	float	dist;
	float	texture_step;
	int		start_x;
	int		end_x;
	float	position_x;
	int		end_y, y;
	int		tex_x;
	int		tex_y;
	float	texture_position;
	char	*value;
	char	*pixel;
}	t_print_ennemy;


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
void			init_textures(t_window *window, char *door);
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
#endif
