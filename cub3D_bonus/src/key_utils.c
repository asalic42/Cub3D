/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:32:15 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/01 17:42:05 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	colision(t_player_pos *player, float dx, float dy)
{
	t_map	*map;
	int		mx;
	int		my;
	int		mp;
	int		i;

	map = get_map_instance();
	i = -1;
	while (++i < 7)
	{
		mx = (int)(player->x + (i * player->dx));
		my = (int)(player->y + (i * player->dy));
		mp = my * map->x + mx;
		if (map->map[mp] == 1 || map->map[mp] == 3)
		{
			player->x -= dx;
			player->y -= dy;
			break ;
		}
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

static void	open_door(void)
{
	t_map			*map;
	t_player_pos	*player;
	int				i;

	player = get_player_instance();
	map = get_map_instance();
	i = -1;
	while (++i < 30)
	{
		map->mx = (int)(player->x + (i * player->dx));
		map->my = (int)(player->y + (i * player->dy));
		map->mp = map->my * map->x + map->mx;
		if (map->map[map->mp] == 3)
		{
			map->map[map->mp] = 4;
			break ;
		}
		else if (map->map[map->mp] == 4)
		{
			map->map[map->mp] = 3;
			break ;
		}
	}
}

int	key_press(int keycode, t_window *window)
{
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
	if (keycode == 65507)
		shot_fired(window);
	return (0);
}
