/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 19:06:27 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
	t_line	prout;

	reset(window);
	init_textures(window, "./textures/door_eye_blood.xpm", \
		"./textures/ennemy1.xpm");
	prout = init_rectangle(0, 0, WIDTH, HEIGHT);
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

int	esc_keypress(int keycode, t_window *window)
{
	if (keycode == 65307)
		return (exit_menu(window));
	return (0);
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
