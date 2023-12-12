/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:37:16 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/12 20:55:55 by rciaze           ###   ########.fr       */
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


extern float px,py;
extern int map_x, map_y, map_s;
extern int map[];

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

void draw_map(void);
int	key_press(int keycode, t_window *window);
int	handle_no_event(void *window);
int	create_window(t_window *window);
int	destroy_window(t_window *window);
void draw_player(t_window *window) ;

#endif
