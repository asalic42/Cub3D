/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:36:44 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/10 18:51:06 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	update_window(t_player_pos *player, t_window *window)
{
	is_player_out_of_bouds(player, window);
	draw_player(window);
}

void	key_press_2(int keycode, t_window *window, t_player_pos *player)
{
	if (keycode == 'w')
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
	if (keycode == 'a')
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

static void find_player_dir(t_player_pos *player, char dir)
{
	if (dir == 'N')
		player->a = PI3;
	else if (dir == 'E')
		player->a = 0;
	else if (dir == 'S')
		player->a = PI2;
	else if (dir == 'W')
		player->a = PI;
}

static void	find_player(t_map *map, t_player_pos *player, char **char_map)
{
	int x;
	int y;
	
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (char_map[y][x] == 'N' || char_map[y][x] == 'E' || char_map[y][x] == 'W' || char_map[y][x] == 'S')
			{
				player->x = x * 128;
				player->y = y * 128;
				find_player_dir(player, char_map[y][x]);
				return ;
			}
			x ++;
		}
		y ++;
	}
}

int	create_window(t_window *window)
{
	t_player_pos	*player;
	t_map			*mapp;

	mapp = get_map_instance();
	mapp->map = simple_tab_int(window->data.ptr.map, window);
	if (!mlx_init_stuff(window))
		return (0);
	mapp->x = window->data.ptr.width;
	mapp->y = window->data.ptr.height;
	mapp->s = (WIDTH)/20;
	player = get_player_instance();
	find_player(mapp, player, window->data.ptr.map);
	player->dx = cos(player->a) * 8;
	player->dy = sin(player->a) * 8;
	printf("x = %f, y = %f\n", player->x, player->y);
	return (1);
}

int	destroy_window(t_window *window)
{
	free_mlx_infos();
	printf("avg time by frame = %f, %d total frames rendered\n", prout / compteur, compteur);
	return (mlx_destroy_window(window->mlx_ptr, window->win_ptr));
}