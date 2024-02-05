/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:32:15 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/05 17:07:49 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	colision(t_player_pos *player, float dx, float dy, t_map *map)
{
	int		mx;
	int		my;
	int		mp;
	int		i;
	bool	prout;

	prout = false;
	i = -1;
	while (++i < 5)
	{
		mx = (int)(player->x + (i * dx));
		mp = (int)(player->y) * map->x + mx;
		if (map->map[mp] == 1 || map->map[mp] == 3 || map->map[mp] == 5)
		{
			player->x -= dx;
			prout = true;
		}
		my = (int)(player->y + (i * dy));
		mp = my * map->x + (int)(player->x);
		if (map->map[mp] == 1 || map->map[mp] == 3 || map->map[mp] == 5)
		{
			player->y -= dy;
			prout = true;
		}
		if (prout)
			break ;
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
	int				mp;

	player = get_player_instance();
	map = get_map_instance();
	i = -1;
	while (++i < 30)
	{
		map->mx = (int)(player->x + (i * player->dx));
		map->my = (int)(player->y + (i * player->dy));
		mp = map->my * map->x + map->mx;
		if (map->map[mp] == 3)
		{
			map->map[mp] = 4;
			break ;
		}
		else if (map->map[mp] == 4)
		{
			map->map[mp] = 3;
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
		shot_fired(window, get_player_instance(), get_map_instance(), \
			get_textures_instance());
	return (0);
}
