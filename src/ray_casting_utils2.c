/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:24:20 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/22 19:17:03 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	init_ray(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->player = get_player_instance();
	all_stuff->map = get_map_instance();
	all_stuff->ra = all_stuff->player->a - DR * BLOCK_SIZE;
	if (all_stuff->ra < 0)
		all_stuff->ra += 2 * PI;
	if (all_stuff->ra > 2 * PI)
		all_stuff->ra -= 2 * PI;
}

void	init_distances(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->dof = 0;
	all_stuff->dist_h = 1000000;
	all_stuff->hx = all_stuff->player->x;
	all_stuff->hy = all_stuff->player->y;
	all_stuff->a_tan = -1 / tan(all_stuff->ra);
	all_stuff->dist_v = 1000000;
	all_stuff->vx = all_stuff->player->x;
	all_stuff->vy = all_stuff->player->y;
	all_stuff->n_tan = -tan(all_stuff->ra);
}

void	calculate_line_height(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->ca = all_stuff->player->a - all_stuff->ra;
	if (all_stuff->ca < 0)
		all_stuff->ca += 2 * PI;
	if (all_stuff->ca > 2 * PI)
		all_stuff->ca -= 2 * PI;
	all_stuff->dist_t = all_stuff->dist_t * cos(all_stuff->ca);
	all_stuff->line_h = (all_stuff->map->s * 640) / all_stuff->dist_t;
	if (all_stuff->line_h > 640)
	{
		all_stuff->original_line_h = all_stuff->line_h;
		all_stuff->line_h = 640;
	}
	all_stuff->line_off = 320 - all_stuff->line_h / 2;
}

void	increment_angle(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->ra += DR;
	if (all_stuff->ra < 0)
		all_stuff->ra += 2 * PI;
	if (all_stuff->ra > 2 * PI)
		all_stuff->ra -= 2 * PI;
}
