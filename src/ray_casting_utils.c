/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:11:12 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/09 16:41:34 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	up_or_down(t_all_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	if (all_stuff->ra > PI)
	{	
		all_stuff->ry = (((int)all_stuff->player->y / (BLOCK_SIZE)) * (BLOCK_SIZE))
			- 0.0001;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->a_tan + all_stuff->player->x;
		all_stuff->horizontal_yo = -(BLOCK_SIZE);
		all_stuff->horizontal_xo = -all_stuff->horizontal_yo * all_stuff->a_tan;
	}
	if (all_stuff->ra < PI)
	{
		all_stuff->ry = (((int)all_stuff->player->y / (BLOCK_SIZE)) * (BLOCK_SIZE))
			+ (BLOCK_SIZE);
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->a_tan + all_stuff->player->x;
		all_stuff->horizontal_yo = (BLOCK_SIZE);
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
		t_all_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	while (all_stuff->dof < all_stuff->map->y)
	{
		all_stuff->mx = (int)(all_stuff->rx) / (BLOCK_SIZE);
		all_stuff->my = (int)(all_stuff->ry) / (BLOCK_SIZE);
		all_stuff->mp = all_stuff->my * all_stuff->map->x + all_stuff->mx;
		if (all_stuff->mp > 0 && all_stuff->mp < all_stuff->map->x
			* all_stuff->map->y && all_stuff->map->map[all_stuff->mp] == 1)
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

void	left_or_right(t_all_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	all_stuff->dof = 0;
	if (all_stuff->ra > PI2 && all_stuff->ra < PI3)
	{
		all_stuff->rx = (((int)all_stuff->player->x / (BLOCK_SIZE)) * (BLOCK_SIZE))
			- 0.0001;
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->n_tan + all_stuff->player->y;
		all_stuff->vertical_xo = -(BLOCK_SIZE);
		all_stuff->vertical_yo = -all_stuff->vertical_xo * all_stuff->n_tan;
	}
	if (all_stuff->ra < PI2 || all_stuff->ra > PI3)
	{
		all_stuff->rx = (((int)all_stuff->player->x / (BLOCK_SIZE)) * (BLOCK_SIZE))
			+ (BLOCK_SIZE);
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->n_tan + all_stuff->player->y;
		all_stuff->vertical_xo = (BLOCK_SIZE);
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
		t_all_stuff_for_ray_casting *all_stuff, t_window *window)
{
	(void)(window);
	while (all_stuff->dof < all_stuff->map->x)
	{
		all_stuff->mx = (int)(all_stuff->rx) / (BLOCK_SIZE);
		all_stuff->my = (int)(all_stuff->ry) / (BLOCK_SIZE);
		all_stuff->mp = all_stuff->my * all_stuff->map->x + all_stuff->mx;
		if (all_stuff->mp > 0 && all_stuff->mp < all_stuff->map->x
			* all_stuff->map->y && all_stuff->map->map[all_stuff->mp] == 1)
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

int	comp_distance(t_all_stuff_for_ray_casting *all_stuff, t_mlx_stuff *img, t_window *window)
{
	int	return_value;

	return_value = 0;
	if (all_stuff->dist_v < all_stuff->dist_h)
	{
		all_stuff->rx = all_stuff->vx;
		all_stuff->ry = all_stuff->vy;
		all_stuff->dist_t = all_stuff->dist_v;
		if (all_stuff->horizontal_xo < 0)
			return_value = 2;
		else
			return_value = 4;
	}
	else if (all_stuff->dist_h < all_stuff->dist_v)
	{
		all_stuff->rx = all_stuff->hx;
		all_stuff->ry = all_stuff->hy;
		all_stuff->dist_t = all_stuff->dist_h;
		if (all_stuff->vertical_yo < 0)
			return_value = 1;
		else
			return_value = 3;
	}
	//draw_line(init_rectangle(all_stuff->rx - 1, all_stuff->ry - 1,
	//		all_stuff->rx + 2, all_stuff->ry + 2), img->img_ptr, 0x00FF00, 0, window);
	(void)(window);
	(void)(img);
	return (return_value);
}
