/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:40:31 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/23 15:11:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	move_player(t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();
	rotation(player, window);
	move_up(player, window);
	move_down(player, window);
	move_right_left(player, window);
	draw_player(window);
	return (0);
}

void	rotation(t_player_pos *player, t_window	*window)
{
	if (window->keys.left)
	{
		player->a -= 0.05;
		if (player->a < 0)
			player->a += 2 * PI;
		player->dx = cos(player->a) * 0.08;
		player->dy = sin(player->a) * 0.08;
	}
	if (window->keys.right)
	{
		player->a += 0.05;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
		player->dx = cos(player->a) * 0.08;
		player->dy = sin(player->a) * 0.08;
	}
}

void	move_up(t_player_pos *player, t_window *window)
{
	if (window->keys.w)
	{
		if (window->keys.a || window->keys.d)
		{
			player->x += player->dx / 1.5;
			player->y += player->dy / 1.5;
			colision(player, player->dx / 1.5, player->dy / 1.5);
		}
		else
		{
			player->x += player->dx;
			player->y += player->dy;
			colision(player, player->dx, player->dy);
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
			colision(player, -(player->dx / 1.5), -(player->dy / 1.5));
		}
		else
		{
			player->x -= player->dx;
			player->y -= player->dy;
			colision(player, -(player->dx), -(player->dy));
		}
	}
}

void	move_right_left(t_player_pos *player, t_window *window)
{
	if (window->keys.a)
	{
		player->y -= player->dx;
		player->x += player->dy;
		colision(player, player->dy, -player->dx);
	}
	if (window->keys.d)
	{
		player->y += player->dx;
		player->x -= player->dy;
		colision(player, -player->dy, player->dx);
	}
}