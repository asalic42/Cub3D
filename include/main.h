/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:37:16 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 18:49:45 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "../minilibx-linux/mlx.h"
#include "../line/includes/line.h"
#include "../rectangle/includes/rectangle.h"
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

#define PI 3.1415926535
#define PI2 PI/2
#define PI3 3*PI/2
#define DR 0.0174533/2
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
} t_window;

typedef struct s_player_pos
{
	float x;
	float y;
	float dx;
	float dy;
	float a;
} t_player_pos;

typedef struct s_map
{
	int		x;
	int		y;
	int		s;
	int 	*map;
} t_map;

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
	float			xo;
	float			yo;
	float			disH;
	float			disT;
	float			hx;	
	float			hy;
	float			aTan;
	float			disV;
	float			vx;
	float			vy;
	float			nTan;
	float			ca;
	float			lineH;
	float			lineO;
	t_line			line;
	unsigned int	color;
	t_player_pos	*player;
	t_map			*map;
} t_all_stuff_for_ray_casting;

void			draw_map(void);
int				key_press(int keycode, t_window *window);
int				handle_no_event(void *window);
int				create_window(t_window *window);
int				destroy_window(t_window *window);
void			draw_player(t_window *window);
t_map			*get_map_instance(void);
t_player_pos	*get_player_instance(void);

#endif
