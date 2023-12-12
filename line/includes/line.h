/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:03:42 by raphael           #+#    #+#             */
/*   Updated: 2023/12/12 20:08:32 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <stdio.h>
# include <unistd.h>
# include "../../minilibx-linux/mlx.h"
# include "basique_mlx_needed.h"

# define ESC		65307

typedef struct c_tmp_pixel
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;
}t_tmp_pixel;

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	width;
}	t_line;

typedef struct s_data_for_line
{
	int		ex;
	int		ey;
	int		dx;
	int		dy;
	int		dx2;
	int		dy2;
	int		x_incr;
	int		y_incr;
	char	*img_data;
	int		img_width;
	int		bits_per_pixel;
}	t_data_for_line;

void	stuff_for_line_draw(t_data_for_line *data, t_line *line, void *img);
void	case_1(t_line *line, t_data_for_line *data, unsigned int color);
void	case_2(t_line *line, t_data_for_line *data, unsigned int color);
int		ft_abs(int n);
void	draw_line(t_line line, void *img, int color);
void	draw_actual_pixels_case_1(t_data_for_line *data, t_line *line,
			unsigned int color);
void	draw_actual_pixels_case_2(t_data_for_line *data, t_line *line,	
			unsigned int color);
t_line	init_line(int x1, int y1, int x2, int y2);

#endif
