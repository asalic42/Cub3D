/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/05 14:33:45 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cast_ray(t_window *window)
{
	t_stuff_for_ray_casting		all_stuff;
	int							comp;
	t_textures_path				*textures;

	init_ray(&all_stuff, window);
	textures = get_textures_instance();
	all_stuff.r = -1;
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
		wich_texture(comp, textures, window, &all_stuff);
		increment_angle(&all_stuff);
	}
}

void	is_player_out_of_bouds(t_player_pos *player, t_window *window)
{
	(void)(window);
	if ((int)player->y > window->data.ptr.height)
		player->y = 1;
	else if ((int)player->y <= 0)
		player->y = (window->data.ptr.height - 1);
	else if ((int)player->x > window->data.ptr.width)
		player->x = 1;
	else if ((int)player->x <= 0)
		player->x = (window->data.ptr.width - 1);
}

void	draw_player(t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();
	draw_line(init_rectangle(0, 0, (WIDTH), (HEIGHT) / 2), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->ceiling), 0);
	draw_line(init_rectangle(0, (HEIGHT) / 2, WIDTH, HEIGHT), window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->floor), 0);
	is_player_out_of_bouds(player, window);
	cast_ray(window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
		window->img_ptr, 0, 0);
	update_mlx_infos(window->mlx_ptr, window->win_ptr, window->img_ptr);
}

int	main(int ac, char **av)
{
	t_window	window;

	if (ac != 2)
		return (print_error(RED "Error : not enought args\n" NC));
	start_garbage();
	handle_error(&window, av[1]);
	if (!create_window(&window))
		return (0);
	update_mlx_infos(&window.mlx_ptr, &window.win_ptr, &window.img_ptr);
	init_textures(window.north, window.west, window.south, window.east);
	mlx_loop_hook(window.mlx_ptr, &move_player, &window);
	mlx_hook(window.win_ptr, 17, KeyPressMask, &destroy_window, &window);
	mlx_hook(window.win_ptr, KeyPress, 0, &key_press, &window);
	mlx_hook(window.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &window);
	mlx_loop(window.mlx_ptr);
	return (1);
}
