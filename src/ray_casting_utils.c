/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:11:12 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/21 15:24:27 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	up_or_down(t_all_stuff_for_ray_casting *all_stuff)
{
	if (all_stuff->ra > PI)
	{	
		all_stuff->ry = (((int)all_stuff->player->y / 64) * 64) - 0.0001;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->a_tan + all_stuff->player->x;
		all_stuff->yo = -64;
		all_stuff->xo = -all_stuff->yo * all_stuff->a_tan;
	}
	if (all_stuff->ra < PI)
	{
		all_stuff->ry = (((int)all_stuff->player->y / 64) * 64) + 64;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->a_tan + all_stuff->player->x;
		all_stuff->yo = 64;
		all_stuff->xo = -all_stuff->yo * all_stuff->a_tan;
	}
	if (all_stuff->ra == 0 || all_stuff->ra == PI)
	{
		all_stuff->rx = all_stuff->player->x;
		all_stuff->ry = all_stuff->player->y;
		all_stuff->dof = 10;
	}
}

void	find_closest_horizontal_intersection(
		t_all_stuff_for_ray_casting *all_stuff)
{
	while (all_stuff->dof < 10)
	{
		all_stuff->mx = (int)(all_stuff->rx) / 64;
		all_stuff->my = (int)(all_stuff->ry) / 64;
		all_stuff->mp = all_stuff->my * all_stuff->map->x + all_stuff->mx;
		if (all_stuff->mp > 0 && all_stuff->mp < all_stuff->map->x
			* all_stuff->map->y && all_stuff->map->map[all_stuff->mp] == 1)
		{
			all_stuff->dof = 10;
			all_stuff->hx = all_stuff->rx;
			all_stuff->hy = all_stuff->ry;
			all_stuff->dist_h = distance(all_stuff->player->x,
					all_stuff->player->y, all_stuff->hx, all_stuff->hy);
		}
		else
		{
			all_stuff->rx += all_stuff->xo;
			all_stuff->ry += all_stuff->yo;
			all_stuff->dof += 1;
		}
	}
}

void	left_or_right(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->dof = 0;
	if (all_stuff->ra > PI2 && all_stuff->ra < PI3)
	{
		all_stuff->rx = (((int)all_stuff->player->x / 64) * 64) - 0.0001;
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->n_tan + all_stuff->player->y;
		all_stuff->xo = -64;
		all_stuff->yo = -all_stuff->xo * all_stuff->n_tan;
	}
	if (all_stuff->ra < PI2 || all_stuff->ra > PI3)
	{
		all_stuff->rx = (((int)all_stuff->player->x / 64) * 64) + 64;
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->n_tan + all_stuff->player->y;
		all_stuff->xo = 64;
		all_stuff->yo = -all_stuff->xo * all_stuff->n_tan;
	}
	if (all_stuff->ra == 0 || all_stuff->ra == PI)
	{
		all_stuff->ry = all_stuff->player->y;
		all_stuff->rx = all_stuff->player->x;
		all_stuff->dof = 10;
	}
}

void	find_closest_vertical_intersection(
		t_all_stuff_for_ray_casting *all_stuff)
{
	while (all_stuff->dof < 10)
	{
		all_stuff->mx = (int)(all_stuff->rx) / 64;
		all_stuff->my = (int)(all_stuff->ry) / 64;
		all_stuff->mp = all_stuff->my * all_stuff->map->x + all_stuff->mx;
		if (all_stuff->mp > 0 && all_stuff->mp < all_stuff->map->x
			* all_stuff->map->y && all_stuff->map->map[all_stuff->mp] == 1)
		{
			all_stuff->dof = 10;
			all_stuff->vx = all_stuff->rx;
			all_stuff->vy = all_stuff->ry;
			all_stuff->dist_v = distance(all_stuff->player->x,
					all_stuff->player->y, all_stuff->vx, all_stuff->vy);
		}
		else
		{
			all_stuff->rx += all_stuff->xo;
			all_stuff->ry += all_stuff->yo;
			all_stuff->dof += 1;
		}
	}
}

void	comp_distance(t_all_stuff_for_ray_casting *all_stuff, t_mlx_stuff *img)
{
	if (all_stuff->dist_v < all_stuff->dist_h)
	{
		all_stuff->rx = all_stuff->vx;
		all_stuff->ry = all_stuff->vy;
		all_stuff->dist_t = all_stuff->dist_v;
		all_stuff->color = mlx_get_color_value(img->mlx_ptr, 0x0000A0);
	}
	else if (all_stuff->dist_h < all_stuff->dist_v)
	{
		all_stuff->rx = all_stuff->hx;
		all_stuff->ry = all_stuff->hy;
		all_stuff->dist_t = all_stuff->dist_h;
		all_stuff->color = mlx_get_color_value(img->mlx_ptr, 0x0000FF);
	}
	draw_line(init_rectangle(all_stuff->rx - 1, all_stuff->ry - 1,
			all_stuff->rx + 2, all_stuff->ry + 2), img->img_ptr, 0x00FF00, 0);
}
