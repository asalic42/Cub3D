/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:51:28 by asalic            #+#    #+#             */
/*   Updated: 2024/02/01 14:19:25 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	keys_rotation(t_player_pos *player, t_window *window, \
		int current_x)
{
	mlx_mouse_get_pos(window->mlx_ptr, window->win_ptr, \
	&window->win.mouse_x, &window->win.mouse_y);
	if (window->keys.left || window->win.mouse_x < current_x)
	{
		player->a -= 0.05;
		if (player->a < 0)
			player->a += 2 * PI;
		player->dx = cos(player->a) * 0.16;
		player->dy = sin(player->a) * 0.16;
	}
	if (window->keys.right || window->win.mouse_x > current_x)
	{
		player->a += 0.05;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
		player->dx = cos(player->a) * 0.16;
		player->dy = sin(player->a) * 0.16;
	}
}

void	rotation(t_player_pos *player, t_window	*window)
{
	int	current_x;

	current_x = window->win.mouse_x;
	if (current_x == 1919 || current_x == 0)
	{
		mlx_mouse_move(window->mlx_ptr, window->win_ptr, WIDTH / 2, \
		HEIGHT / 2);
		mlx_mouse_get_pos(window->mlx_ptr, window->win_ptr, \
		&window->win.mouse_x, &window->win.mouse_y);
	}
	else
		keys_rotation(player, window, current_x);
}
