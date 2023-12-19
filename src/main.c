/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 19:46:51 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

#include <time.h> 

double prout;int compteur = 0;

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	init_ray(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->player = get_player_instance();
	all_stuff->map = get_map_instance();
	all_stuff->ra = all_stuff->player->a - DR * 64;
	if (all_stuff->ra < 0)
		all_stuff->ra += 2 * PI;
	if (all_stuff->ra > 2 * PI)
		all_stuff->ra -= 2 * PI;
}

void	up_or_down(t_all_stuff_for_ray_casting *all_stuff)
{
	if (all_stuff->ra > PI)
	{	
		all_stuff->ry = (((int)all_stuff->player->y / 64) * 64) - 0.0001;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->aTan + all_stuff->player->x;
		all_stuff->yo = -64;
		all_stuff->xo = -all_stuff->yo * all_stuff->aTan;
	}
	if (all_stuff->ra < PI)
	{
		all_stuff->ry = (((int)all_stuff->player->y / 64) * 64) + 64;
		all_stuff->rx = (all_stuff->player->y - all_stuff->ry)
			* all_stuff->aTan + all_stuff->player->x;
		all_stuff->yo = 64;
		all_stuff->xo = -all_stuff->yo * all_stuff->aTan;
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
			all_stuff->disH = distance(all_stuff->player->x,
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
			* all_stuff->nTan + all_stuff->player->y;
		all_stuff->xo = -64;
		all_stuff->yo = -all_stuff->xo * all_stuff->nTan;
	}
	if (all_stuff->ra < PI2 || all_stuff->ra > PI3)
	{
		all_stuff->rx = (((int)all_stuff->player->x / 64) * 64) + 64;
		all_stuff->ry = (all_stuff->player->x - all_stuff->rx)
			* all_stuff->nTan + all_stuff->player->y;
		all_stuff->xo = 64;
		all_stuff->yo = -all_stuff->xo * all_stuff->nTan;
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
			all_stuff->disV = distance(all_stuff->player->x,
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

void	init_distances(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->dof = 0;
	all_stuff->disH = 1000000;
	all_stuff->hx = all_stuff->player->x;
	all_stuff->hy = all_stuff->player->y;
	all_stuff->aTan = -1 / tan(all_stuff->ra);
	all_stuff->disV = 1000000;
	all_stuff->vx = all_stuff->player->x;
	all_stuff->vy = all_stuff->player->y;
	all_stuff->nTan = -tan(all_stuff->ra);
}

void	comp_distance(t_all_stuff_for_ray_casting *all_stuff, t_mlx_stuff *img)
{
	if (all_stuff->disV < all_stuff->disH)
	{
		all_stuff->rx = all_stuff->vx;
		all_stuff->ry = all_stuff->vy;
		all_stuff->disT = all_stuff->disV;
		all_stuff->color = mlx_get_color_value(img->mlx_ptr, 0x0000A0);
	}
	else if (all_stuff->disH < all_stuff->disV)
	{
		all_stuff->rx = all_stuff->hx;
		all_stuff->ry = all_stuff->hy;
		all_stuff->disT = all_stuff->disH;
		all_stuff->color = mlx_get_color_value(img->mlx_ptr, 0x0000FF);
	}
	draw_line(init_rectangle(all_stuff->rx - 1, all_stuff->ry - 1,
			all_stuff->rx + 2, all_stuff->ry + 2), img->img_ptr, 0x00FF00, 0);
}

void	calculate_line_height(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->ca = all_stuff->player->a - all_stuff->ra;
	if (all_stuff->ca < 0)
		all_stuff->ca += 2 * PI;
	if (all_stuff->ca > 2 * PI)
		all_stuff->ca -= 2 * PI;
	all_stuff->disT = all_stuff->disT * cos(all_stuff->ca);
	all_stuff->lineH = (all_stuff->map->s * 500) / all_stuff->disT;
	if (all_stuff->lineH > 500)
		all_stuff->lineH = 500;
	all_stuff->lineO = 320 - all_stuff->lineH / 2;
}

void	increment_angle(t_all_stuff_for_ray_casting *all_stuff)
{
	all_stuff->ra += DR;
	if (all_stuff->ra < 0)
		all_stuff->ra += 2 * PI;
	if (all_stuff->ra > 2 * PI)
		all_stuff->ra -= 2 * PI;
}

void	cast_ray()
{
	t_mlx_stuff					*img = get_mlx_ptr();
	t_all_stuff_for_ray_casting	all_stuff;
	clock_t start = clock();

	init_ray(&all_stuff);
	all_stuff.r = 0;
	while (++all_stuff.r < 128)
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff);
		find_closest_horizontal_intersection(&all_stuff);
		left_or_right(&all_stuff);
		find_closest_vertical_intersection(&all_stuff);
		comp_distance(&all_stuff, img);
		all_stuff.line = init_line(all_stuff.player->x, all_stuff.player->y,
				all_stuff.rx, all_stuff.ry);
		all_stuff.line.width = 1;
		draw_line(all_stuff.line, img->img_ptr, 0x000050, 64);
		calculate_line_height(&all_stuff);
		all_stuff.line = init_line(all_stuff.r * 5 + 640, all_stuff.lineH
				+ all_stuff.lineO, all_stuff.r * 5 + 640, all_stuff.lineO);
		all_stuff.line.width = 5;
		draw_line(all_stuff.line, img->img_ptr, all_stuff.color, 0);
		increment_angle(&all_stuff);
	}
	clock_t end = clock();
	prout = (double)(end - start) / CLOCKS_PER_SEC;
	compteur++;
}

void	is_player_out_of_bouds(t_player_pos *player)
{
	if (player->y > 640)
		player->y = 0;
	if (player->y < 0)
		player->y = 640;
	if (player->x > 640)
		player->x = 0;
	if (player->x < 0)
		player->x = 640;
}

void draw_player(t_window *window)
{	
	t_line			line;
	t_player_pos	*player;

	player = get_player_instance();
	draw_line(init_rectangle(0, 0, 640, 640), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, 0x555555), 0);
	draw_line(init_rectangle(640, 0, 1280, 320), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, 0x651684), 0);
	draw_line(init_rectangle(640, 320, 1280, 640), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, 0x665464), 0);
	is_player_out_of_bouds(player);
	draw_map();
	cast_ray();
	draw_line(init_rectangle(player->x - 5, player->y - 5, player->x + 5,
			player->y + 5), window->img_ptr, 0xFFFF00, 5);
	line = init_line(player->x, player->y, player->x + player->dx * 5,
			player->y + player->dy * 5);
	line.width = 2;
	draw_line(line, window->img_ptr, 0xFFFF00, 1);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
		window->img_ptr, 0, 0);
}

void draw_map(void)
{
	int			x;
	int			y;
	int			x0;
	int			y0;
	t_mlx_stuff	*img;
	t_map		*map;

	img = get_mlx_ptr();
	map = get_map_instance();
	y = -1;
	while (++y < map->y)
	{
		y0 = y * map->s;
		x = -1;
		while (++x < map->x)
		{
			x0 = x * map->s;
			if (map->map[y * map->x + x] == 1)
				draw_line(init_rectangle(x0, y0, x0 + map->s - 3, y0 +
						map->s - 1), img->img_ptr, 0x0F0F0F, 0);
			else
				draw_line(init_rectangle(x0, y0, x0 + map->s - 3, y0 +
						map->s - 1), img->img_ptr, 0xC0C0C0, 0);
		}
	}
}

int main() {
	t_window	window;

	if (!create_window(&window))
		return (0);
	update_mlx_infos(&window.mlx_ptr, &window.win_ptr, &window.img_ptr);
	draw_player(&window);
	mlx_loop_hook(window.mlx_ptr, &handle_no_event, &window);
	mlx_hook(window.win_ptr, 17, KeyPressMask, &destroy_window, &window);
	mlx_hook(window.win_ptr, 2, KeyPressMask, &key_press, &window);
	mlx_loop(window.mlx_ptr);
	return (1);
}
