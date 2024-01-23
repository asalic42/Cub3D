/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 23:57:06 by raphael           #+#    #+#             */
/*   Updated: 2024/01/23 18:32:52 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/forme.h"

//	The breseham algorithm is here used with two cases.
//	You could optimize it more by doing other cases, but it's not necessary.

void	draw_line(t_line line, void *img, int color, int stop)
{
	t_data_for_line	data;

	stuff_for_line_draw(&data, &line, img);
	if (data.dx2 > data.dy2)
		case_1(&line, &data, color, stop);
	else
		case_2(&line, &data, color, stop);
}

//	These two function are used to calculate the alghorithm.
//	No pixels are drawn here.
//	The algorithm, as you can see, is very simple.
//	I will not explain it here,
//	but you can find very good explanations of it on youtube.

void	case_1(t_line *line, t_data_for_line *data, unsigned int color, \
				int stop)
{
	int				i;

	i = -1;
	while (i <= data->dx2)
	{
		if (line->x1 < stop || line->x1 > (WIDTH) - stop || line->y1 < stop \
		|| line->y1 > (HEIGHT) - stop)
			break ;
		draw_actual_pixels_case_1(data, line, color);
		i++;
		line->x1 += data->x_incr;
		data->ex -= data->dy2;
		if (data->ex < 0)
		{
			line->y1 += data->y_incr;
			data->ex += data->dx2;
		}
	}
}

void	case_2(t_line *line, t_data_for_line *data, unsigned int color, \
				int stop)
{
	int	i;

	i = -1;
	while (i <= data->dy2)
	{
		if (line->x1 < stop || line->x1 > (WIDTH) - stop || line->y1 < stop \
		|| line->y1 > (HEIGHT) - stop)
			break ;
		draw_actual_pixels_case_2(data, line, color);
		i++;
		line->y1 += data->y_incr;
		data->ey -= data->dx2;
		if (data->ey < 0)
		{
			line->x1 += data->x_incr;
			data->ey += data->dy2;
		}
	}
}

//	These two functions are used to draw the actual pixels.
//	No calculations are done here, : we just draw the pixels.

void	draw_actual_pixels_case_1(t_data_for_line *data, t_line *line,
		unsigned int color)
{
	char			*pixel_offset;
	int				w;

	pixel_offset = data->img_data + (line->y1 * data->img_width + line->x1)
		* (data->bits_per_pixel);
	*(unsigned int *)pixel_offset = color;
	w = 0;
	while (++w <= line->width / 2)
	{
		pixel_offset = data->img_data + ((line->y1 - w)
				* data->img_width + line->x1) * (data->bits_per_pixel);
		*(unsigned int *)pixel_offset = color;
		if (w != line->width / 2 || line->width % 2 == 1)
		{
			pixel_offset = data->img_data + ((line->y1 + w)
					* data->img_width + line->x1) * (data->bits_per_pixel);
			*(unsigned int *)pixel_offset = color;
		}
	}
}

void	draw_actual_pixels_case_2(t_data_for_line *data, t_line *line,	
		unsigned int color)
{
	char			*pixel_offset;
	int				w;

	pixel_offset = data->img_data + (line->y1 * data->img_width + line->x1)
		* (data->bits_per_pixel);
	*(unsigned int *)pixel_offset = color;
	w = 0;
	while (++w <= line->width / 2)
	{
		pixel_offset = data->img_data + (line->y1 * data->img_width
				+ (line->x1 - w)) * (data->bits_per_pixel);
		*(unsigned int *)pixel_offset = color;
		if (w != line->width / 2 || line->width % 2 == 1)
		{
			pixel_offset = data->img_data + (line->y1 * data->img_width
					+ (line->x1 + w)) * (data->bits_per_pixel);
			*(unsigned int *)pixel_offset = color;
		}
	}
}
