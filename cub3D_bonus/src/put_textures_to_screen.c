/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures_to_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:09:49 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/23 17:58:01 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	calculations(t_put_texture_to_img_data *variables,
	t_stuff_for_ray_casting *all_stuff, int *end_y, t_texture_details *xpm)
{
	variables->y = all_stuff->line_off;
	*end_y = variables->y + all_stuff->line_h;
	variables->current_x = all_stuff->r;
	variables->texture_step = (float)xpm->height / all_stuff->line_h;
	if (all_stuff->dist_h > all_stuff->dist_v)
		variables->tex_x = (int)(all_stuff->ry * xpm->width) % xpm->width;
	else
		variables->tex_x = (int)(all_stuff->rx * xpm->width) % xpm->width;
	if (variables->tex_x < 0)
		variables->tex_x = 0;
	variables->texture_position = 0;
	if (variables->y < 0)
	{
		variables->texture_position += variables->texture_step
			* (-variables->y);
		variables->y += -variables->y;
	}
}

void	texture_to_screen(t_stuff_for_ray_casting *all_stuff,
	t_texture_details *xpm, void *img_data, int comp)
{
	t_put_texture_to_img_data	variables;
	int							end_y;

	calculations(&variables, all_stuff, &end_y, xpm);
	if (comp == 2 || comp == 3)
		variables.tex_x = xpm->width - variables.tex_x;
	while (variables.y < end_y && variables.y < HEIGHT)
	{
		if (variables.y >= 0)
		{
			variables.tex_y = (int)(variables.texture_position);
			variables.value = xpm->xpm_data
				+ (variables.tex_y * xpm->width + variables.tex_x) * (4);
			variables.pixel = img_data
				+ (variables.y * (WIDTH) + variables.current_x) * (4);
			*(unsigned int *)variables.pixel = *(unsigned int *)variables.value;
		}
		variables.texture_position += variables.texture_step;
		variables.y++;
	}
}

void	wich_texture(int comp, t_textures_path *textures, t_window *window,
	t_stuff_for_ray_casting *all_stuff)
{
	if (comp == 1)
		texture_to_screen(all_stuff, &textures->xpm1, window->img_data, comp);
	else if (comp == 2)
		texture_to_screen(all_stuff, &textures->xpm2, window->img_data, comp);
	else if (comp == 3)
		texture_to_screen(all_stuff, &textures->xpm3, window->img_data, comp);
	else if (comp == 4)
		texture_to_screen(all_stuff, &textures->xpm4, window->img_data, comp);
	else if (comp == 5)
		texture_to_screen(all_stuff, &textures->xpm_door, window->img_data, \
		comp);
}
