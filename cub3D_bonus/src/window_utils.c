/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:30:50 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/05 16:58:13 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	mlx_init_stuff(t_window *window)
{
	window->bits = 4;
	window->size_line_img = WIDTH;
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		return (0);
	window->win_ptr = mlx_new_window(window->mlx_ptr, WIDTH, HEIGHT, "cub");
	if (window->win_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_ptr = mlx_new_image(window->mlx_ptr, WIDTH, HEIGHT);
	if (window->img_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_window
			(window->mlx_ptr, window->win_ptr), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_data = (mlx_get_data_addr(window->img_ptr, &(window->bits),
				&(window->size_line_img), &(window->endian)));
	if (window->img_data == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_image
			(window->mlx_ptr, window->img_ptr), mlx_destroy_window
			(window->mlx_ptr, window->win_ptr), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	return (1);
}

void	fps_init(void)
{
	t_fps			*fps;

	fps = get_fps_instance();
	fps->compteur = 0;
}

int	create_window(t_window *window)
{
	t_player_pos	*player;
	t_map			*mapp;

	fps_init();
	mapp = get_map_instance();
	mapp->map = simple_tab_int(window->data.ptr.map, window, -1);
	if (!mlx_init_stuff(window))
		return (0);
	mapp->x = window->data.ptr.width;
	mapp->y = window->data.ptr.height;
	mapp->mp = mapp->x * mapp->y;
	player = get_player_instance();
	find_player(mapp, player, window->data.ptr.map);
	player->dx = cos(player->a) * 0.16;
	player->dy = sin(player->a) * 0.16;
	window->keys.a = false;
	window->keys.s = false;
	window->keys.w = false;
	window->keys.d = false;
	window->keys.left = false;
	window->keys.right = false;
	window->win.mouse_x = 0;
	window->win.mouse_y = 0;
	window->anim_bool = false;
	return (1);
}

int	destroy_window(t_window *window)
{
	free_mlx_infos();
	window->stop = true;
	pthread_join(window->sound.audio, NULL);
	if (window->sound.wav_buffer)
		SDL_FreeWAV(window->sound.wav_buffer);
	if (window->sound.audio_device)
		SDL_CloseAudioDevice(window->sound.audio_device);
	if (window->sound.init)
		SDL_Quit();
	exit(EXIT_SUCCESS);
}

int	exit_menu(t_window *window)
{
	t_mlx_stuff		*mlx_infos;

	mlx_infos = get_mlx_ptr();
	if (window->menu.img_data)
		mlx_destroy_image(mlx_infos->mlx_ptr, window->menu.img_data);
	if (mlx_infos->img_ptr)
		mlx_destroy_image(mlx_infos->mlx_ptr, mlx_infos->img_ptr);
	mlx_destroy_window(mlx_infos->mlx_ptr, mlx_infos->win_ptr);
	ft_printf(GREEN"Window is closing\n"NC);
	mlx_destroy_display(mlx_infos->mlx_ptr);
	free_garbage();
	free(mlx_infos->mlx_ptr);
	exit(EXIT_SUCCESS);
}
