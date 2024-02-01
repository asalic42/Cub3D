/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:24:20 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/01 14:58:30 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	init_ray(t_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	all_stuff->player = get_player_instance();
	all_stuff->map = get_map_instance();
	all_stuff->ra = all_stuff->player->a - R_FOV / 2 + (R_FOV / NB_OF_STRIPES * (300 / (WIDTH / NB_OF_STRIPES)));
	all_stuff->ra = normalize_angle(all_stuff->ra);
}

void	init_distances(t_stuff_for_ray_casting *all_stuff)
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

void	calculate_line_height(t_stuff_for_ray_casting *all_stuff,
	t_window *window)
{
	(void)(window);
	// all_stuff->ca = atan2(all_stuff->player->a, all_stuff->ra);
	all_stuff->ca = all_stuff->ra - all_stuff->player->a;
	all_stuff->ca = normalize_angle(all_stuff->ca);
	all_stuff->dist_t *= cos(all_stuff->ca) * 0.7647059;
	all_stuff->line_h = (HEIGHT) / (all_stuff->dist_t);
	all_stuff->line_off = (HEIGHT) / 1.9 - all_stuff->line_h / 2;
}

void	increment_angle(t_stuff_for_ray_casting *all_stuff)
{
	all_stuff->ra += R_FOV / NB_OF_STRIPES;
	if (all_stuff->ra < 0)
		all_stuff->ra += 2 * PI;
	if (all_stuff->ra > 2 * PI)
		all_stuff->ra -= 2 * PI;
}
