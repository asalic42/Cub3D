/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:40:31 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 17:23:00 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	move_player(t_window *window)
{
	t_player_pos	*player;
	static clock_t	start;
	static clock_t	end;
	float			time;

	end = clock();
	time = (float)(end - start) / CLOCKS_PER_SEC;
	if (time > 0 && time < (double)1 / 60)
		usleep ((((double)1 / 60) - time) * 1000000);
	start = clock();
	player = get_player_instance();
	rotation(player, window);
	move_up(player, window);
	move_down(player, window);
	move_right_left(player, window);
	draw_player(window);
	return (0);
}

void	move_up(t_player_pos *player, t_window *window)
{
	if (window->keys.w)
	{
		if (window->keys.a || window->keys.d)
		{
			player->x += player->dx / 1.5;
			player->y += player->dy / 1.5;
			colision(player, player->dx / 1.5, player->dy / 1.5, \
				get_map_instance());
		}
		else
		{
			player->x += player->dx;
			player->y += player->dy;
			colision(player, player->dx, player->dy, get_map_instance());
		}
	}
}

void	move_down(t_player_pos *player, t_window *window)
{
	if (window->keys.s)
	{
		if (window->keys.a || window->keys.d)
		{
			player->x -= player->dx / 1.5;
			player->y -= player->dy / 1.5;
			colision(player, -(player->dx / 1.5), -(player->dy / 1.5), \
				get_map_instance());
		}
		else
		{
			player->x -= player->dx;
			player->y -= player->dy;
			colision(player, -(player->dx), -(player->dy), get_map_instance());
		}
	}
}

void	move_right_left(t_player_pos *player, t_window *window)
{
	if (window->keys.a)
	{
		player->y -= player->dx;
		player->x += player->dy;
		colision(player, player->dy, -player->dx, get_map_instance());
	}
	if (window->keys.d)
	{
		player->y += player->dx;
		player->x -= player->dy;
		colision(player, -player->dy, player->dx, get_map_instance());
	}
}
