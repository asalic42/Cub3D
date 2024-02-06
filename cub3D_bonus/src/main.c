/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 18:24:19 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cast_ray(t_window *window)
{
	t_stuff_for_ray_casting		all_stuff;
	int							comp;
	t_textures_path				*textures;
	t_fps						*fps;

	fps = get_fps_instance();
	init_ray(&all_stuff, window);
	textures = get_textures_instance();
	all_stuff.r = 300 / (WIDTH / NB_OF_STRIPES);
	all_stuff.player = get_player_instance();
	while (++all_stuff.r < NB_OF_STRIPES - 300 / (WIDTH / NB_OF_STRIPES))
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff, window);
		find_closest_horizontal_intersection(&all_stuff, window);
		left_or_right(&all_stuff, window);
		find_closest_vertical_intersection(&all_stuff, window);
		comp = comp_distance(&all_stuff);
		all_stuff.lenght_tab[all_stuff.r] = all_stuff.line_h;
		calculate_line_height(&all_stuff, window);
		wich_texture(comp, textures, window, &all_stuff);
		increment_angle(&all_stuff);
	}
	ennemy(textures, &all_stuff, window);
	fps->compteur++;
}

void	draw_and_count_fps(t_player_pos *player, t_window *win)
{
	t_fps			*fps;
	int				temps;

	fps = get_fps_instance();
	if (((double)(fps->end - fps->start) / CLOCKS_PER_SEC) > 1.5)
	{
		fps->start += ((double)(fps->end - fps->start)) / 2;
		fps->t_compteur /= 2;
	}
	cast_ray(win);
	fps->end = clock();
	fps->t_compteur++;
	temps = 0;
	temps = (int)(fps->t_compteur / ((double)(fps->end - fps->start)
				/ CLOCKS_PER_SEC));
	draw_map(win, player, get_map_instance());
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
		win->img_ptr, 0, 0);
	fps->str = ft_strjoin("Fps = ", ft_itoa(temps));
	ennemy_animation(win);
	weapon_animation(win);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 1800, 50, 0xFFFFFF, fps->str);
}

void	draw_player(t_window *window)
{	
	t_player_pos	*player;
	static t_line	ceilling;
	static t_line	floor;

	player = get_player_instance();
	if (!ceilling.width)
		ceilling = init_rectangle(300, 150, (WIDTH) - 300, (HEIGHT) / 1.9);
	if (!floor.width)
		floor = init_rectangle(300, (HEIGHT) / 1.9, WIDTH - 300, HEIGHT - 150);
	draw_line(ceilling, window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->ceiling), 0);
	draw_line(floor, window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->floor), 0);
	is_player_out_of_bouds(player, window);
	draw_and_count_fps(player, window);
	update_mlx_infos(window->mlx_ptr, window->win_ptr, window->img_ptr);
}

void	reset(t_window *window)
{
	t_mlx_stuff		*mlx_infos;

	mlx_infos = get_mlx_ptr();
	mlx_destroy_image(mlx_infos->mlx_ptr, window->menu.img_data);
	if (mlx_infos->img_ptr)
		mlx_destroy_image(mlx_infos->mlx_ptr, mlx_infos->img_ptr);
	mlx_destroy_window(mlx_infos->mlx_ptr, mlx_infos->win_ptr);
	mlx_destroy_display(mlx_infos->mlx_ptr);
	free(mlx_infos->mlx_ptr);
	if (!create_window(window))
	{
		free_garbage();
		exit(EXIT_FAILURE);
	}
	update_mlx_infos(&window->mlx_ptr, &window->win_ptr, &window->img_ptr);
}

void	start_game(t_window *window)
{
	reset(window);
	init_textures(window, "./textures/door_eye_blood.xpm", "./textures/ennemy1.xpm");
	t_line prout = init_rectangle(0, 0, WIDTH, HEIGHT);
	draw_line(prout, window->img_ptr, 0x690000, 0);
	initializer_audio(window);
	pthread_create(&window->sound.audio, NULL, (void (*))play_music, window);
	mlx_loop_hook(window->mlx_ptr, &move_player, window);
	mlx_hook(window->win_ptr, 17, KeyPressMask, &destroy_window, window);
	mlx_hook(window->win_ptr, KeyPress, 0, &key_press, window);
	mlx_hook(window->win_ptr, KeyRelease, KeyReleaseMask, &key_release, window);
	mlx_loop(window->mlx_ptr);
	destroy_window(window);
}

int	button_press(int mousepress, int x, int y, t_window *window)
{
	if (mousepress == 1 && x >= 786 && x <= 1186 && y >= 523 && y <= 576)
		start_game(window);
	else if (mousepress == 1 && x >= 915 && x <= 1031 && y >= 635 && y <= 692)	
		exit_menu(window);
	return (0);
}

int	mouse_pos(t_window *window)
{
	t_mlx_stuff *mlx;

	mlx = get_mlx_ptr();
	mlx_mouse_get_pos(window->mlx_ptr, window->win_ptr, \
	&window->win.mouse_x, &window->win.mouse_y);
	if (window->win.mouse_x >= 786 && window->win.mouse_x <= 1186 &&window->win.mouse_y >= 523 && window->win.mouse_y <= 576)
	{
		mlx_destroy_image(mlx->mlx_ptr, window->menu.img_data);
		window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/start_choose.xpm",
			&window->menu.width, &window->menu.height);
		mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->menu.img_data, 0, 0);
	}
	else if (window->win.mouse_x >= 915 && window->win.mouse_x <= 1031 && window->win.mouse_y >= 635 && window->win.mouse_y <= 692)
	{
		mlx_destroy_image(mlx->mlx_ptr, window->menu.img_data);
		window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/exit_choose.xpm",
			&window->menu.width, &window->menu.height);
		mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->menu.img_data, 0, 0);
	}
	else
	{
		mlx_destroy_image(mlx->mlx_ptr, window->menu.img_data);
		window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/new_menu.xpm",
			&window->menu.width, &window->menu.height);
		mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->menu.img_data, 0, 0);
	}
	return (1);
}

int esc_keypress(int keycode, t_window *window)
{
	if (keycode == 65307)
		return (exit_menu(window));
	return (0);
}

void	create_menu(t_window *window)
{
	t_mlx_stuff *mlx;
	
	mlx = get_mlx_ptr();
	window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/new_menu.xpm",
			&window->menu.width, &window->menu.height);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->menu.img_data, 0, 0);
	mlx_loop_hook(window->mlx_ptr, &mouse_pos, window);
	mlx_hook(window->win_ptr, ButtonPress, ButtonPressMask, &button_press, window);
	mlx_hook(window->win_ptr, 17, ButtonPressMask, &exit_menu, window);
	mlx_hook(window->win_ptr, KeyPress, KeyPressMask, &esc_keypress, window);
	mlx_loop(window->mlx_ptr);
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
	create_menu(&window);
	return (1);
}
