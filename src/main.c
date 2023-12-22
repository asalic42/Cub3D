/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/22 20:14:11 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

#include <time.h> 

double prout;int compteur = 0;

void test2(int x, int start_y, int end_y, t_mlx_stuff *window, t_all_stuff_for_ray_casting *all_stuff, char *xpm_data, int xpm_width, int xpm_height, void *img_data)
{
	t_textures	textures;

	(void)(window);
	textures.current_x = x;
	textures.texture_step = (float)xpm_height / all_stuff->line_h;
	textures.tex_x = (int)(all_stuff->rx) % xpm_width;
	if (textures.tex_x == 0 || textures.tex_x == xpm_width - 1 || textures.tex_x == xpm_width / 2)
		textures.tex_x = (int)(all_stuff->ry) % xpm_width;
	if (start_y == 0 && end_y == 640)
	{
		textures.texture_step = (float)xpm_height / all_stuff->original_line_h;
		start_y = 320 - all_stuff->original_line_h / 2;
		end_y = all_stuff->original_line_h;	
	}
	while (textures.current_x < x + 6)
	{
		textures.y = start_y;
		textures.texture_position = 0;
		while (textures.y < end_y && textures.y < 640)
		{
			if (textures.y >= 0)
			{
				textures.tex_y = (int)(textures.texture_position);
				textures.value = xpm_data + (textures.tex_y * xpm_width + textures.tex_x) * (4);
				textures.pixel = img_data + (textures.y * WIDTH + textures.current_x) * (4);
				*(unsigned int *)textures.pixel = *(unsigned int *)textures.value;
			}
			textures.texture_position += textures.texture_step;
			textures.y++;
		}
		textures.current_x++;
	}
}



void	cast_ray()
{
	t_mlx_stuff					*img;
	t_all_stuff_for_ray_casting	all_stuff;
	clock_t						start;
	clock_t						end;
	int							x;
	int							comp;

	img = get_mlx_ptr();
	init_ray(&all_stuff);
	all_stuff.r = -1;
	start = clock();
	all_stuff.player = get_player_instance();
	int xpm_width1;
	int xpm_height1;
	t_tmp_pixel		tmp_p;
	void *xpm1 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/rock-wall-32x32.xpm", &xpm_width1, &xpm_height1);
	void *xpm_data1 = mlx_get_data_addr(xpm1, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int xpm_width2;
	int xpm_height2;
	void *xpm2 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/stone.xpm", &xpm_width2, &xpm_height2);
	void *xpm_data2 = mlx_get_data_addr(xpm2, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int xpm_width3;
	int xpm_height3;
	void *xpm3 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/wall_3.xpm", &xpm_width3, &xpm_height3);
	void *xpm_data3 = mlx_get_data_addr(xpm3, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int xpm_width4;
	int xpm_height4;
	void *xpm4 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/7sB6yU3.xpm", &xpm_width4, &xpm_height4);
	void *xpm_data4 = mlx_get_data_addr(xpm4, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	void *img_data = mlx_get_data_addr(img->img_ptr, &tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	while (++all_stuff.r < 106)
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff);
		find_closest_horizontal_intersection(&all_stuff);
		left_or_right(&all_stuff);
		find_closest_vertical_intersection(&all_stuff);
		comp = comp_distance(&all_stuff, img);
		all_stuff.line = init_line(all_stuff.player->x, all_stuff.player->y,
				all_stuff.rx, all_stuff.ry);
		all_stuff.line.width = 1;
		draw_line(all_stuff.line, img->img_ptr, 0x000050, 64);
		calculate_line_height(&all_stuff);
		x = all_stuff.r * 6 + 640;
		if (comp == 1)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, img, &all_stuff, xpm_data1, xpm_width1, xpm_height1, img_data);
		else if (comp == 2)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, img, &all_stuff, xpm_data2, xpm_width2, xpm_height2, img_data);
		else if (comp == 3)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, img, &all_stuff, xpm_data3, xpm_width3, xpm_height3, img_data);
		else if (comp == 4)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, img, &all_stuff, xpm_data4, xpm_width4, xpm_height4, img_data);
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
