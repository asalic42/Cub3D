/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:37:16 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/22 20:14:39 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../minilibx-linux/mlx.h"
# include "../line/includes/line.h"
# include "../rectangle/includes/rectangle.h"
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
# define DR 0.0174533 / 2

extern double prout;
extern int compteur;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits;
	int		size_line_img;
	int		endian;
}	t_window;

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
	int		s;
	int		minimap_s;
	int 	*map;
}	t_map;

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

void			draw_map(t_mlx_stuff *img, t_map *map);
int				key_press(int keycode, t_window *window);
int				handle_no_event(void *window);
int				create_window(t_window *window);
int				destroy_window(t_window *window);
void			draw_player(t_window *window);
t_map			*get_map_instance(void);
t_player_pos	*get_player_instance(void);
void			up_or_down(t_all_stuff_for_ray_casting *all_stuff);
void			find_closest_horizontal_intersection(
					t_all_stuff_for_ray_casting *all_stuff);
void			left_or_right(t_all_stuff_for_ray_casting *all_stuff);
void			find_closest_vertical_intersection(
					t_all_stuff_for_ray_casting *all_stuff);
float			distance(float ax, float ay, float bx, float by);
int				comp_distance(t_all_stuff_for_ray_casting *all_stuff,
					t_mlx_stuff *img);
float			distance(float ax, float ay, float bx, float by);
void			init_ray(t_all_stuff_for_ray_casting *all_stuff);
void			init_distances(t_all_stuff_for_ray_casting *all_stuff);
void			calculate_line_height(t_all_stuff_for_ray_casting *all_stuff);
void			increment_angle(t_all_stuff_for_ray_casting *all_stuff);
void			is_player_out_of_bouds(t_player_pos *player);
#endif
