/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:36:44 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/09 13:50:02 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	update_window(t_player_pos *player, t_window *window)
{
	is_player_out_of_bouds(player, window);
	draw_player(window);
}

void	key_press_2(int keycode, t_window *window, t_player_pos *player)
{
	if (keycode == 'z')
	{
		player->x += player->dx;
		player->y += player->dy;
		update_window(player, window);
	}
	if (keycode == 's')
	{
		player->x -= player->dx;
		player->y -= player->dy;
		update_window(player, window);
	}
}

int	key_press(int keycode, t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();
	if (keycode == 65307)
		return (destroy_window(window));
	if (keycode == 'q')
	{
		player->a -= 0.1;
		if (player->a < 0)
			player->a += 2 * PI;
		player->dx = cos(player->a) * 5;
		player->dy = sin(player->a) * 5;
		update_window(player, window);
	}
	if (keycode == 'd')
	{
		player->a += 0.1;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
		player->dx = cos(player->a) * 5;
		player->dy = sin(player->a) * 5;
		update_window(player, window);
	}
	key_press_2(keycode, window, player);
	return (0);
}

int	handle_no_event(void *window)
{
	(void)(window);
	return (0);
}

int	mlx_init_stuff(t_window *window)
{
	window->bits = 3;
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

int	create_window(t_window *window)
{
	t_player_pos	*player;
	t_map			*map;
	int prout[100] = 
	{1,1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,1,1,0,1,
	1,0,0,0,0,1,0,1,0,1,
	1,0,0,0,0,1,0,1,0,1,
	1,0,1,0,0,1,0,1,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1};

	if (!mlx_init_stuff(window))
		return (0);
	player = get_player_instance();
	player->a = DR;
	player->x = 300;
	player->y = 300;
	player->dx = cos(player->a) * 10;
	player->dy = sin(player->a) * 10;
	map = get_map_instance();
	map->x = 10;
	map->y = 10;
	map->s = (WIDTH)/20;
	map->map = ft_malloc(100 * sizeof(int));
	ft_memcpy(map->map, prout, 100 * sizeof(int));
	return (1);
}

int	destroy_window(t_window *window)
{
	free_mlx_infos();
	printf("avg time by frame = %f, %d total frames rendered\n", prout / compteur, compteur);
	return (mlx_destroy_window(window->mlx_ptr, window->win_ptr));
}