/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:36:44 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 18:43:49 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	key_press(int keycode, t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();
	if (keycode == 65307)
		return (destroy_window(window));
	if (keycode == 'a') 
	{
		player->a -= 0.1;
		if (player->a < 0)
			player->a += 2* PI;
		player->dx = cos(player->a) * 5;
		player->dy = sin(player->a) * 5;
	}
	if (keycode == 'd')
	{
		player->a += 0.1;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
		player->dx = cos(player->a) * 5;
		player->dy = sin(player->a) * 5;
	}
	if (keycode == 'w')
	{
		player->x += player->dx;
		player->y += player->dy;
	}
	if (keycode == 's')
	{
		player->x -= player->dx;
		player->y -= player->dy;
	}
	if (player->y > 640)
		player->y = 0;
	if (player->y < 0)
		player->y = 640;
	if (player->x > 640)
		player->x = 0;
	if (player->x < 0)
		player->x = 640;
	mlx_destroy_image(window->mlx_ptr, window->img_ptr);
	window->img_ptr = mlx_new_image(window->mlx_ptr, 1280, 640);
	window->img_data = (mlx_get_data_addr(window->img_ptr, &(window->bits),
				&(window->size_line_img), &(window->endian)));
	draw_player(window);
	return (0);
}

int	handle_no_event(void *window)
{
	(void)(window);
	return (0);
}

int	create_window(t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();	
	window->bits = 3;
	window->size_line_img = 1280;
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		return (0);
	window->win_ptr = mlx_new_window(window->mlx_ptr, 1280, 640, "cub");
	if (window->win_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_ptr = mlx_new_image(window->mlx_ptr, 1280, 640);
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
	player->x = 300;
	player->y = 300;
	player->dx = cos(player->a) * 5;
	player->dy = sin(player->a) * 5;
	t_map	*map;

	map = get_map_instance();
	map->x = 10;
	map->y = 10;
	map->s = 64;
	map->map = malloc(100 * sizeof(int));
	
	int prout[100] = 
	{1,1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,1,1,0,1,
	1,0,1,0,0,1,0,1,0,1,
	1,0,0,0,0,1,0,1,0,1,
	1,0,0,0,0,1,0,1,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1};

	memcpy(map->map, prout, 100 * sizeof(int));
	return (1);
}

int	destroy_window(t_window *window)
{
	printf("avg time by frame = %f, %d total frames rendered\n", prout / compteur, compteur);
	return (mlx_destroy_window(window->mlx_ptr, window->win_ptr));
}