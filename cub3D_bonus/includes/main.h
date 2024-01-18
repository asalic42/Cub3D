/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by rciaze            #+#    #+#             */
/*   Updated: 2024/01/18 18:19:08 by asalic           ###   ########.fr       */
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
# define PI2 PI / 2
# define PI3 3*PI / 2
# define DR 0.00054541666

extern double	prout;
extern int		compteur;

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
	int		x;
	int		y;
	int		*map;
}	t_map;

typedef	struct s_textures_path
{
	int				xpm_width1;
	int				xpm_height1;
	void			*xpm1;
	void			*xpm_data1;
	int				xpm_width2;
	int				xpm_height2;
	void			*xpm2;
	void			*xpm_data2;
	int				xpm_width3;
	int				xpm_height3;
	void			*xpm3;
	void			*xpm_data3;
	int				xpm_width4;
	int				xpm_height4;
	void			*xpm4;
	void			*xpm_data4;
	int				is_init;
}	t_textures_path;


typedef struct s_all_stuff_for_ray_casting
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
}	t_all_stuff_for_ray_casting;

typedef struct s_textures
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
}	t_textures;

t_textures_path	*get_textures_instance(void);
void			draw_map(t_mlx_stuff *img, t_map *map);
int				key_press(int keycode, t_window *window);
int				handle_no_event(void *window);
int				create_window(t_window *window);
int				*simple_tab_int(char **char_map, t_window *window);
int				destroy_window(t_window *window);
void			draw_player(t_window *window);
t_map			*get_map_instance(void);
t_player_pos	*get_player_instance(void);
void			up_or_down(t_all_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			find_closest_horizontal_intersection(
					t_all_stuff_for_ray_casting *all_stuff, t_window *window);
void			left_or_right(t_all_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			find_closest_vertical_intersection(
					t_all_stuff_for_ray_casting *all_stuff, t_window *window);
float			distance(float ax, float ay, float bx, float by);
int				comp_distance(t_all_stuff_for_ray_casting *all_stuff);
float			distance(float ax, float ay, float bx, float by);
void			init_ray(t_all_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			init_distances(t_all_stuff_for_ray_casting *all_stuff);
void			calculate_line_height(t_all_stuff_for_ray_casting *all_stuff, \
					t_window *window);
void			increment_angle(t_all_stuff_for_ray_casting *all_stuff);
void			is_player_out_of_bouds(t_player_pos *player, t_window *window);
#endif
