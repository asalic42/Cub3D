/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:27:15 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/29 14:22:38 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

float	normalize_angle(float angle)
{	
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	calculate_angle(t_window *window, t_print_ennemy *data,
	t_stuff_for_ray_casting *all_stuff)
{
	data->x_vector = window->ennemy.x - all_stuff->player->x;
	data->y_vector = window->ennemy.y - all_stuff->player->y;
	data->lenght = sqrt(data->x_vector * data->x_vector + data->y_vector
			* data->y_vector);
	data->x_vector /= data->lenght;
	data->y_vector /= data->lenght;
	data->target_angle = atan2(data->y_vector, data->x_vector);
	data->relative_angle = data->target_angle - all_stuff->player->a;
	data->relative_angle = normalize_angle(data->relative_angle) * 180 / PI;
	if (data->relative_angle > 325 && data->relative_angle < 360)
		data->relative_angle -= 360;
	data->relative_angle *= -1;
	data->relative_angle += 35;
	data->relative_angle = 70 - data->relative_angle;
	data->save = data->relative_angle * (960 / 70);
}

void	draw_ennemy(t_window *window, t_print_ennemy *data,
	t_textures_path *textures)
{
	while (data->y < data->end_y && data->y < HEIGHT)
	{
		data->tex_y = (int)(data->texture_position);
		data->value = textures->xpm_ennemy.xpm_data
			+ (data->tex_y * textures->xpm_ennemy.width + data->tex_x) * (4);
		if (*(unsigned int *)data->value != 0x00FF00)
		{
			data->pixel = window->img_data + (data->y * WIDTH
					+ data->start_x) * 4;
			*(unsigned int *)data->pixel = *(unsigned int *)data->value;
			*(unsigned int *)(data->pixel + 4) = *(unsigned int *)data->value;
		}
		data->texture_position += data->texture_step;
		data->y++;
	}
}

void	x_loop(t_window *window, t_print_ennemy *data, t_textures_path *textures
	, t_stuff_for_ray_casting *all_stuff)
{
	while (data->start_x < data->end_x && data->start_x < WIDTH)
	{
		if (data->dist < all_stuff->lenght_tab[data->start_x / 2])
		{
			data->y = ((HEIGHT) / 2) - all_stuff->line_h / 2;
			data->end_y = data->y + all_stuff->line_h;
			data->tex_x = (int)(data->position_x);
			data->texture_position = 0;
			if (data->y < 0)
			{
				data->texture_position = data->texture_step * data->y;
				data->y += -data->y;
			}
			if (data->texture_position < 0)
				data->texture_position = 0;
			draw_ennemy(window, data, textures);
		}
		data->position_x += data->texture_step;
		data->start_x++;
	}
}

void	ennemy(t_textures_path *textures, t_stuff_for_ray_casting *all_stuff,
	t_window *window)
{
	t_print_ennemy	data;

	calculate_angle(window, &data, all_stuff);
	if (data.relative_angle >= 0 && data.relative_angle <= 70)
	{
		data.dist = (distance(all_stuff->player->x, all_stuff->player->y,
					window->ennemy.x, window->ennemy.y));
		all_stuff->line_h = (HEIGHT + 650) / data.dist;
		data.texture_step = (float)textures->xpm_ennemy.height
			/ all_stuff->line_h;
		data.position_x = 0;
		data.start_x = data.save * 2;
		data.end_x = data.start_x + all_stuff->line_h;
		if (data.start_x < 0)
		{
			data.position_x = data.texture_step * data.start_x;
			data.start_x += -data.start_x;
		}
		x_loop(window, &data, textures, all_stuff);
	}
}
