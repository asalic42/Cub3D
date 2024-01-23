/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:40:31 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/23 19:08:13 by asalic           ###   ########.fr       */
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

void	rotation(t_player_pos *player, t_window	*window)
{
	int	current_x;
	int	current_y;

	current_x = window->win.mouse_x;
	current_y = window->win.mouse_y;
	mlx_mouse_get_pos(window->mlx_ptr, window->win_ptr, &window->win.mouse_x, \
	&window->win.mouse_y);
	if (window->keys.left || window->win.mouse_x < current_x || \
	window->win.mouse_x <= 0)
	{
		player->a -= 0.05;
		if (player->a < 0)
			player->a += 2 * PI;
		player->dx = cos(player->a) * 0.12;
		player->dy = sin(player->a) * 0.12;
	}
	if (window->keys.right || window->win.mouse_x > current_x || \
	window->win.mouse_x >= 1919)
	{
		player->a += 0.05;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
		player->dx = cos(player->a) * 0.12;
		player->dy = sin(player->a) * 0.12;
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
