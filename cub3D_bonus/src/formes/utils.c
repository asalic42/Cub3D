/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:06:16 by raphael           #+#    #+#             */
/*   Updated: 2024/01/23 18:25:28 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

// This function is used to initialize a line structure.
// It's not necessary, but it's cleaner to use it.
// It allows you to save line, in order to make the norme happy.

t_line	init_line(int x1, int y1, int x2, int y2)
{
	t_line	line;

	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
	line.y2 = y2;
	return (line);
}

//	If you can use abs, use it. It's much faster than our implementation.
//	We can't reproduce exactly the function, because of... 
//	You guessed it, the norm.If not, use this.

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

//	This function simply initializes all the variables we need to draw the line,
//	as well as storing some data on the img we are drawing to, for... the norm.

void	stuff_for_line_draw(t_data_for_line *data, t_line *line, void *img)
{
	t_tmp_pixel		tmp_p;

	data->img_data = mlx_get_data_addr(img, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	data->img_width = (WIDTH);
	data->bits_per_pixel = 4;
	data->ex = ft_abs(line->x2 - line->x1);
	data->ey = ft_abs(line->y2 - line->y1);
	data->dx = data->ex * 2;
	data->dy = data->ey * 2;
	data->dx2 = data->ex;
	data->dy2 = data->ey;
	data->x_incr = 1;
	data->y_incr = 1;
	if (line->x1 > line->x2)
		data->x_incr = -1;
	if (line->y1 > line->y2)
		data->y_incr = -1;
}

t_line	init_rectangle(int x1, int y1, int x2, int y2)
{
	t_line	rectangle;

	rectangle.x1 = x1;
	rectangle.y1 = (y1 + y2) / 2;
	rectangle.x2 = x2;
	rectangle.y2 = rectangle.y1;
	rectangle.width = ft_abs(y2 - y1);
	return (rectangle);
}
