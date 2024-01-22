/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:32:15 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/22 17:14:07 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	colision(t_player_pos *player, float dx, float dy)
{
	t_map	*map;
	int		mx;
	int		my;
	int		mp;

	map = get_map_instance();
	mx = (int)player->x;
	my = (int)player->y;
	mp = my * map->x + mx;
	if (map->map[mp] == 1 || map->map[mp] == 3)
	{
		player->y -= dy;
		player->x -= dx;
	}
}

int	key_release(int keycode, t_window *window)
{
	if (window->keys.w && keycode == 'w')
		window->keys.w = false;
	if (window->keys.a && keycode == 'a')
		window->keys.a = false;
	if (window->keys.s && keycode == 's')
		window->keys.s = false;
	if (window->keys.d && keycode == 'd')
		window->keys.d = false;
	if (window->keys.left && keycode == 65361)
		window->keys.left = false;
	if (window->keys.right && keycode == 65363)
		window->keys.right = false;
	return (1);
}

void	open_door()
{
	t_map	*map;
	int		mp;
	int		mx;
	int		my;

	t_player_pos *player = get_player_instance();
	map = get_map_instance();
	mx = (int)player->x + (10 * player->dx);
	my = (int)player->y + (10 * player->dy);
	mp = my * map->x + mx;
	if (map->map[mp] == 3)
		map->map[mp] = 4;
	else if (map->map[mp] == 4)
		map->map[mp] = 3;
}

int	key_press(int keycode, t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();
	if (keycode == 65307)
		return (destroy_window(window));
	if (!window->keys.w && keycode == 'w')
		window->keys.w = true;
	if (!window->keys.a && keycode == 'a')
		window->keys.a = true;
	if (!window->keys.s && keycode == 's')
		window->keys.s = true;
	if (!window->keys.d && keycode == 'd')
		window->keys.d = true;
	if (keycode == 'e')
		open_door();
	if (!window->keys.left && keycode == 65361)
		window->keys.left = true;
	if (!window->keys.right && keycode == 65363)
		window->keys.right = true;
	return (0);
}
