/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:32:15 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 17:58:32 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	detect_colision(float dx, int mp, t_map *map, t_player_pos *player)
{
	if (map->map[mp] == 1 || map->map[mp] == 3 || map->map[mp] == 5)
	{
		player->x -= dx;
		map->boum = true;
	}
}

/* Detect if there is a collision between the player and a wall */
void	colision(t_player_pos *player, float dx, float dy, t_map *map)
{
	int		mx;
	int		my;
	int		mp;
	int		i;

	map->boum = false;
	i = -1;
	while (++i < 5)
	{
		mx = (int)(player->x + (i * dx));
		mp = (int)(player->y) * map->x + mx;
		detect_colision(dx, mp, map, player);
		my = (int)(player->y + (i * dy));
		mp = my * map->x + (int)(player->x);
		if (map->map[mp] == 1 || map->map[mp] == 3 || map->map[mp] == 5)
		{
			player->y -= dy;
			map->boum = true;
		}
		if (map->boum)
			break ;
	}
}

/* Key released handle */
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

/* Check if the door is open or close an change it */
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

/* Key press handle */
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
