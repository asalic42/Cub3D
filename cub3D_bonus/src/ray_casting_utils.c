/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:11:12 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/26 15:30:26 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	up_or_down(t_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	if (all_stuff->ra > PI)
	{	
		all_stuff->ry = (int)all_stuff->player->y - 0.0001;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->a_tan + all_stuff->player->x;
		all_stuff->horizontal_yo = -1;
		all_stuff->horizontal_xo = -all_stuff->horizontal_yo * all_stuff->a_tan;
	}
	if (all_stuff->ra < PI)
	{
		all_stuff->ry = (int)all_stuff->player->y + 1;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->a_tan + all_stuff->player->x;
		all_stuff->horizontal_yo = 1;
		all_stuff->horizontal_xo = -all_stuff->horizontal_yo * all_stuff->a_tan;
	}
	if (all_stuff->ra == 0 || all_stuff->ra == PI)
	{
		all_stuff->rx = all_stuff->player->x;
		all_stuff->ry = all_stuff->player->y;
		all_stuff->dof = all_stuff->map->y;
	}
}

void	find_closest_horizontal_intersection(
		t_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	while (all_stuff->dof < all_stuff->map->y)
	{
		all_stuff->mx = (int)all_stuff->rx;
		all_stuff->my = (int)all_stuff->ry;
		all_stuff->mp = all_stuff->my * all_stuff->map->x + all_stuff->mx;
		if (all_stuff->mp > 0 && all_stuff->mp < all_stuff->map->x \
		* all_stuff->map->y && (all_stuff->map->map[all_stuff->mp] == 1 || \
		all_stuff->map->map[all_stuff->mp] == 3))
		{
			all_stuff->dof = all_stuff->map->y;
			all_stuff->hx = all_stuff->rx;
			all_stuff->hy = all_stuff->ry;
			all_stuff->dist_h = distance(all_stuff->player->x,
					all_stuff->player->y, all_stuff->hx, all_stuff->hy);
		}
		else
		{
			all_stuff->rx += all_stuff->horizontal_xo;
			all_stuff->ry += all_stuff->horizontal_yo;
			all_stuff->dof += 1;
		}
	}
}

void	left_or_right(t_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	all_stuff->dof = 0;
	if (all_stuff->ra > PI2 && all_stuff->ra < PI3)
	{
		all_stuff->rx = (int)all_stuff->player->x - 0.0001;
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->n_tan + all_stuff->player->y;
		all_stuff->vertical_xo = -1;
		all_stuff->vertical_yo = -all_stuff->vertical_xo * all_stuff->n_tan;
	}
	if (all_stuff->ra < PI2 || all_stuff->ra > PI3)
	{
		all_stuff->rx = (int)all_stuff->player->x + 1;
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->n_tan + all_stuff->player->y;
		all_stuff->vertical_xo = 1;
		all_stuff->vertical_yo = -all_stuff->vertical_xo * all_stuff->n_tan;
	}
	if (all_stuff->ra == 0 || all_stuff->ra == PI)
	{
		all_stuff->ry = all_stuff->player->y;
		all_stuff->rx = all_stuff->player->x;
		all_stuff->dof = all_stuff->map->x;
	}
}

void	find_closest_vertical_intersection(
		t_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	while (all_stuff->dof < all_stuff->map->x)
	{
		all_stuff->mx = (int)all_stuff->rx;
		all_stuff->my = (int)all_stuff->ry;
		all_stuff->mp = all_stuff->my * all_stuff->map->x + all_stuff->mx;
		if (all_stuff->mp > 0 && all_stuff->mp < all_stuff->map->x \
		* all_stuff->map->y && (all_stuff->map->map[all_stuff->mp] == 1 || \
		all_stuff->map->map[all_stuff->mp] == 3))
		{
			all_stuff->dof = all_stuff->map->x;
			all_stuff->vx = all_stuff->rx;
			all_stuff->vy = all_stuff->ry;
			all_stuff->dist_v = distance(all_stuff->player->x,
					all_stuff->player->y, all_stuff->vx, all_stuff->vy);
		}
		else
		{
			all_stuff->rx += all_stuff->vertical_xo;
			all_stuff->ry += all_stuff->vertical_yo;
			all_stuff->dof += 1;
		}
	}
}

int	comp_distance(t_stuff_for_ray_casting *all_stuff)
{
	int	return_value;

	return_value = 0;
	if (all_stuff->dist_v < all_stuff->dist_h)
	{
		all_stuff->dist_t = all_stuff->dist_v;
		if (all_stuff->horizontal_xo < 0)
			return_value = 2;
		else
			return_value = 4;
	}
	else
	{
		all_stuff->rx = all_stuff->hx;
		all_stuff->ry = all_stuff->hy;
		all_stuff->dist_t = all_stuff->dist_h;
		if (all_stuff->vertical_yo < 0)
			return_value = 1;
		else
			return_value = 3;
	}
	if (all_stuff->map->map[(int)all_stuff->ry * all_stuff->map->x + \
		(int)all_stuff->rx] == 3)
		return_value = 5;
	if (all_stuff->map->map[(int)all_stuff->ry * all_stuff->map->x + \
		(int)all_stuff->rx] == 5)
		return_value = 6;
	return (return_value);
}
