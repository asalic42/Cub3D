/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/21 18:05:15 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

#include <time.h> 

double prout;int compteur = 0;

void	test2(int x, int y1, int y2, t_mlx_stuff *window, t_all_stuff_for_ray_casting *all_stuff)
{
	int		j;
	void	*img_data;
	t_tmp_pixel		tmp_p;
	int		bits_per_pixel = 4;
	char	*pixel;
	int		tmp_x = x-1;
	char *value;
	int xpm_width;
	int xpm_height;
	img_data = mlx_get_data_addr(window->img_ptr, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	void *xpm = mlx_xpm_file_to_image(window->mlx_ptr, "./textures/stone.xpm", &xpm_width, &xpm_height);
	void *xpm_data = mlx_get_data_addr(xpm, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int coef = (all_stuff->line_h) / xpm_height;
	value = xpm_data + (0 * 32 + (int)fmod(all_stuff->rx, 64)/2) * bits_per_pixel;
	while(++tmp_x < x + 5)
	{
		int counter = 0;
		j = y1;
		while (++j < y2)
		{

			if (j % coef == 0)
			{
				printf("y = %d, x = %d\n", counter, (int)all_stuff->rx/32);
				value = xpm_data + (counter * 32 + (int)all_stuff->rx/32) * bits_per_pixel;
				counter++;
			}
			pixel = img_data + (j * WIDTH + tmp_x) * bits_per_pixel;
			*(unsigned int *)pixel = *(unsigned int *)value;
		}
	}
}

void	cast_ray()
{
	t_mlx_stuff					*img;
	t_all_stuff_for_ray_casting	all_stuff;
	clock_t						start;
	clock_t						end;
	int							x;

	img = get_mlx_ptr();
	init_ray(&all_stuff);
	all_stuff.r = -1;
	start = clock();
	while (++all_stuff.r < 1)
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
		x = all_stuff.r * 5 + 640;
		test2(x, all_stuff.line_off, all_stuff.line_h + all_stuff.line_off, img, &all_stuff);
		//all_stuff.line = init_line(x, all_stuff.line_h + all_stuff.line_off,
		//		x, all_stuff.line_off);
		//all_stuff.line.width = 5;
		draw_line(all_stuff.line, img->img_ptr, all_stuff.color, 0);
		increment_angle(&all_stuff);
	}
	end = clock();
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

void	draw_player(t_window *window)
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
	draw_map(get_mlx_ptr(), get_map_instance());
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

void	draw_map(t_mlx_stuff *img, t_map *map)
{
	int			x;
	int			y;
	int			x0;
	int			y0;

	y = -1;
	while (++y < map->y)
	{
		y0 = y * map->s;
		x = -1;
		while (++x < map->x)
		{
			x0 = x * map->s;
			if (map->map[y * map->x + x] == 1)
				draw_line(init_rectangle(x0, y0, x0 + map->s - 3, y0
						+ map->s - 1), img->img_ptr, 0x0F0F0F, 0);
			else
				draw_line(init_rectangle(x0, y0, x0 + map->s - 3, y0
						+ map->s - 1), img->img_ptr, 0xC0C0C0, 0);
		}
	}
}

int	main(void)
{
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
