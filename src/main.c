/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/08 19:30:42 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

#include <time.h> 

double prout;int compteur = 0;

void test2(int x, int start_y, int end_y, t_all_stuff_for_ray_casting *all_stuff, char *xpm_data, int xpm_width, int xpm_height, void *img_data, t_window *window)
{
	(void)(window);
	t_textures	textures;

	textures.current_x = x;
	textures.texture_step = (float)xpm_height / all_stuff->line_h;
	if (all_stuff->dist_h > all_stuff->dist_v)
		textures.tex_x = (int)(all_stuff->ry) % xpm_width;
	if (all_stuff->dist_h < all_stuff->dist_v)
		textures.tex_x = (int)(all_stuff->rx) % xpm_width;
	if (start_y == 0 && end_y == HEIGHT)
	{
		textures.texture_step = (float)xpm_height / all_stuff->original_line_h;
		start_y = HEIGHT / 2 - (all_stuff->original_line_h / 2);
		end_y = all_stuff->original_line_h;	
	}
	textures.y = start_y;
	textures.texture_position = 0;
	while (textures.y < end_y && textures.y < HEIGHT)
	{
		if (textures.y >= 0)
		{
			textures.tex_y = (int)(textures.texture_position);
			textures.value = xpm_data + (textures.tex_y * xpm_width + textures.tex_x) * (4);
			textures.pixel = img_data + (textures.y * (WIDTH) + textures.current_x) * (4);
			*(unsigned int *)textures.pixel = *(unsigned int *)textures.value;
		}
		textures.texture_position += textures.texture_step;
		textures.y++;
	}
}

void	cast_ray(t_window *window)
{
	t_mlx_stuff					*img;
	t_all_stuff_for_ray_casting	all_stuff;
	clock_t						start;
	clock_t						end;
	int							x;
	int							comp;
	void						*img_data;

	img = get_mlx_ptr();
	init_ray(&all_stuff, window);
	all_stuff.r = -1;
	start = clock();
	all_stuff.player = get_player_instance();

	int xpm_width1;
	int xpm_height1;
	t_tmp_pixel		tmp_p;
	void *xpm1 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/wall_1.xpm", &xpm_width1, &xpm_height1);
	void *xpm_data1 = mlx_get_data_addr(xpm1, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int xpm_width2;
	int xpm_height2;
	void *xpm2 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/wall_2.xpm", &xpm_width2, &xpm_height2);
	void *xpm_data2 = mlx_get_data_addr(xpm2, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int xpm_width3;
	int xpm_height3;
	void *xpm3 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/wall_3.xpm", &xpm_width3, &xpm_height3);
	void *xpm_data3 = mlx_get_data_addr(xpm3, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	int xpm_width4;
	int xpm_height4;
	void *xpm4 = mlx_xpm_file_to_image(img->mlx_ptr, "./textures/wall_4.xpm", &xpm_width4, &xpm_height4);
	void *xpm_data4 = mlx_get_data_addr(xpm4, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);

	img_data = mlx_get_data_addr(img->img_ptr, &tmp_p.bits_per_pixel, &tmp_p.size_line, &tmp_p.endian);
	while (++all_stuff.r < 1920)
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff, window);
		find_closest_horizontal_intersection(&all_stuff, window);
		left_or_right(&all_stuff, window);
		find_closest_vertical_intersection(&all_stuff, window);
		comp = comp_distance(&all_stuff, img, window);
		//all_stuff.line = init_line(all_stuff.player->x, all_stuff.player->y,
		//		all_stuff.rx, all_stuff.ry);
		// all_stuff.line.width = 1;
		//draw_line(all_stuff.line, img->img_ptr, 0x000050, 64, window);
		calculate_line_height(&all_stuff, window);
		x = all_stuff.r;
		if (comp == 1)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, xpm_data1, xpm_width1, xpm_height1, img_data, window);
		else if (comp == 2)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, xpm_data2, xpm_width2, xpm_height2, img_data, window);
		else if (comp == 3)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, xpm_data3, xpm_width3, xpm_height3, img_data, window);
		else if (comp == 4)
			test2(x, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, xpm_data4, xpm_width4, xpm_height4, img_data, window);
		increment_angle(&all_stuff);
	}
	end = clock();
	prout = (double)(end - start) / CLOCKS_PER_SEC;
	compteur++;
}

void	is_player_out_of_bouds(t_player_pos *player, t_window *window)
{
	(void)(window);
	if (player->y > HEIGHT)
		player->y = 0;
	if (player->y < 0)
		player->y = HEIGHT;
	if (player->x > WIDTH)
		player->x = 0;
	if (player->x < 0)
		player->x = WIDTH;
}

void	draw_player(t_window *window)
{	
	t_line			line;
	t_player_pos	*player;

	player = get_player_instance();
	//draw_line(init_rectangle(0, 0, (WIDTH) / 2, HEIGHT), window->img_ptr,
	//	mlx_get_color_value(window->mlx_ptr, 0x555555), 0, window);
	draw_line(init_rectangle(0, 0, (WIDTH), (HEIGHT) / 2), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, 0x651684), 0, window);
	draw_line(init_rectangle(0, (HEIGHT) / 2, WIDTH, HEIGHT), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, 0x665464), 0, window);
	is_player_out_of_bouds(player, window);
	//draw_map(get_mlx_ptr(), get_map_instance(), window);
	(void)(line);
	cast_ray(window);
	//draw_line(init_rectangle(player->x - 5, player->y - 5, player->x + 5,
	//		player->y + 5), window->img_ptr, 0xFFFF00, 5, window);
	//line = init_line(player->x, player->y, player->x + player->dx * 5,
	//		player->y + player->dy * 5);
	//line.width = 2;
	//draw_line(line, window->img_ptr, 0xFFFF00, 1, window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
		window->img_ptr, 0, 0);
	update_mlx_infos(window->mlx_ptr, window->win_ptr, window->img_ptr);
}

void	draw_map(t_mlx_stuff *img, t_map *map, t_window *window)
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
						+ map->s - 1), img->img_ptr, 0x0F0F0F, 0, window);
			else
				draw_line(init_rectangle(x0, y0, x0 + map->s - 3, y0
						+ map->s - 1), img->img_ptr, 0xC0C0C0, 0, window);
		}
	}
}

int	main(int ac, char **av)
{
	t_window	window;

	(void)(ac);(void)(av);
	//if (ac != 2)
	//	return (print_error(RED "Error : not enought args\n" NC));
	start_garbage();
	//handle_error(&window, av[1]);
	if (!create_window(&window))
		return (0);
	update_mlx_infos(&window.mlx_ptr, &window.win_ptr, &window.img_ptr);
	draw_player(&window);
	mlx_loop_hook(window.mlx_ptr, &handle_no_event, &window);
	mlx_hook(window.win_ptr, 17, KeyPressMask, &destroy_window, &window);
	mlx_hook(window.win_ptr, 2, KeyPressMask, &key_press, &window);
	mlx_loop(window.mlx_ptr);
	close_wndo(&window);
	return (1);
}
