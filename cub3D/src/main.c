/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/18 18:15:50 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

double prout;int compteur = 0;

void test2(int x, int start_y, int end_y, t_all_stuff_for_ray_casting *all_stuff, char *xpm_data, int xpm_width, int xpm_height, void *img_data, t_window *window)
{
    (void)(window);
    t_textures    textures;

	textures.current_x = x;
	textures.texture_step = (float)xpm_height / all_stuff->line_h;
	if (all_stuff->dist_h > all_stuff->dist_v)
		textures.tex_x = (int)(all_stuff->ry * xpm_width) % xpm_width;
	else
		textures.tex_x = (int)(all_stuff->rx * xpm_width) % xpm_width;
	if (start_y == 0 && end_y == HEIGHT)
	{
		textures.texture_step = (float)xpm_height / all_stuff->original_line_h;
		start_y = HEIGHT / 2 - (all_stuff->original_line_h / 2);
		end_y = all_stuff->original_line_h;	
	}
	if (textures.tex_x < 0)
		textures.tex_x = 0;
	textures.y = start_y;
	textures.texture_position = 0;
	if (start_y < 0)
	{
		textures.texture_position += textures.texture_step * (-start_y);
		textures.y += -start_y;
	}
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

void	init_textures(char *path1, char *path2, char *path3, char *path4)
{
	t_textures_path	*textures;
	t_mlx_stuff		*mlx;
	t_tmp_pixel		tmp_p;

	mlx = get_mlx_ptr();
	textures = get_textures_instance();	
	textures->xpm1 = mlx_xpm_file_to_image(mlx->mlx_ptr, path1, &textures->xpm_width1, &textures->xpm_height1);
	textures->xpm_data1 = mlx_get_data_addr(textures->xpm1, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	textures->xpm2 = mlx_xpm_file_to_image(mlx->mlx_ptr, path2, &textures->xpm_width2, &textures->xpm_height2);
	textures->xpm_data2 = mlx_get_data_addr(textures->xpm2, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	textures->xpm3 = mlx_xpm_file_to_image(mlx->mlx_ptr, path3, &textures->xpm_width3, &textures->xpm_height3);
	textures->xpm_data3 = mlx_get_data_addr(textures->xpm3, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
	textures->xpm4 = mlx_xpm_file_to_image(mlx->mlx_ptr, path4, &textures->xpm_width4, &textures->xpm_height4);
	textures->xpm_data4 = mlx_get_data_addr(textures->xpm4, &tmp_p.bits_per_pixel,
			&tmp_p.size_line, &tmp_p.endian);
}

void	cast_ray(t_window *window)
{
	t_all_stuff_for_ray_casting	all_stuff;
	clock_t						start;
	clock_t						end;
	int							comp;
	t_textures_path	*textures;

	textures = get_textures_instance();	
	init_ray(&all_stuff, window);
	all_stuff.r = -1;
	start = clock();
	all_stuff.player = get_player_instance();
	while (++all_stuff.r < 1920)
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff, window);
		find_closest_horizontal_intersection(&all_stuff, window);
		left_or_right(&all_stuff, window);
		find_closest_vertical_intersection(&all_stuff, window);
		comp = comp_distance(&all_stuff);
		calculate_line_height(&all_stuff, window);
		if (comp == 1)
			test2(all_stuff.r, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, textures->xpm_data1, textures->xpm_width1, textures->xpm_height1, window->img_data, window);
		else if (comp == 2)
			test2(all_stuff.r, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, textures->xpm_data2, textures->xpm_width2, textures->xpm_height2, window->img_data, window);
		else if (comp == 3)
			test2(all_stuff.r, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, textures->xpm_data3, textures->xpm_width3, textures->xpm_height3, window->img_data, window);
		else if (comp == 4)
			test2(all_stuff.r, all_stuff.line_off, all_stuff.line_off + all_stuff.line_h, &all_stuff, textures->xpm_data4, textures->xpm_width4, textures->xpm_height4, window->img_data, window);
		increment_angle(&all_stuff);
	}
	end = clock();
	prout = (double)(end - start) / CLOCKS_PER_SEC;
	compteur++;
}

void	is_player_out_of_bouds(t_player_pos *player, t_window *window)
{
	(void)(window);
	if ((int)player->y / 1 > window->data.ptr.height)
	{
		printf("out top of vertical bounds\n");
		player->y = 1;
	}
	else if ((int)player->y / 1 <= 0)
	{
		printf("out bottom of vertical bounds\n");
		player->y = 1 * (window->data.ptr.height - 1);
	}
	else if ((int)player->x / 1 > window->data.ptr.width)
	{
		printf("out right of horizontal bounds\n");
		player->x = 1;
	}
	else if ((int)player->x / 1 <= 0)
	{
		printf("out left of horizontal bounds\n");
		player->x = 1 * (window->data.ptr.width - 1);
	}
}

void	draw_player(t_window *window)
{	
	t_line			line;
	t_player_pos	*player;
	// t_map			*map = get_map_instance();

	player = get_player_instance();
	draw_line(init_rectangle(0, 0, (WIDTH), (HEIGHT) / 2), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->ceiling), 0);
	draw_line(init_rectangle(0, (HEIGHT) / 2, WIDTH, HEIGHT), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->floor), 0);
	is_player_out_of_bouds(player, window);
	(void)(line);
 	/* for (int i = 0; i < window->data.ptr.height; i++) {
		for (int j = 0; j < window->data.ptr.width; j++) {
			if (i == (int)player->y / 1 && j == (int)player->x / 1) {
				write(0, RED, 8);
				char *str = ft_itoa(map->map[i * window->data.ptr.width + j]);
				write(0, str, strlen(str));
				write(0, NC, 5);
			}
			else {
				char *str = ft_itoa(map->map[i * window->data.ptr.width + j]);
				write(0, str, strlen(str));
			}
		}
		write(0, "\n", 1);
	} */
	cast_ray(window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
		window->img_ptr, 0, 0);
	update_mlx_infos(window->mlx_ptr, window->win_ptr, window->img_ptr);
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

int	main(int ac, char **av)
{
	t_window	window;

	(void)(ac);(void)(av);
	if (ac != 2)
		return (print_error(RED "Error : not enought args\n" NC));
	start_garbage();
	handle_error(&window, av[1]);
	horizontal_blocksize = WIDTH / window.data.ptr.width;
	vertical_blocksize = HEIGHT / window.data.ptr.height;
	printf("horizontal_blocksize  = %d, vertical_blocksize = %d\n", horizontal_blocksize, vertical_blocksize);
	printf("window.data.ptr.width  = %d, window.data.ptr.height = %d\n", window.data.ptr.width, window.data.ptr.height);
	//if (horizontal_blocksize > vertical_blocksize)
	//	blocksize = horizontal_blocksize;
	//else
	//	blocksize = vertical_blocksize;
	if (!create_window(&window))	
		return (0);
	update_mlx_infos(&window.mlx_ptr, &window.win_ptr, &window.img_ptr);
	init_textures(window.north, window.west, window.south, window.east);
	draw_player(&window);
	mlx_loop_hook(window.mlx_ptr, &handle_no_event, &window);
	mlx_hook(window.win_ptr, 17, KeyPressMask, &destroy_window, &window);
	mlx_hook(window.win_ptr, 2, KeyPressMask, &key_press, &window);
	mlx_loop(window.mlx_ptr);
	return (1);
}
