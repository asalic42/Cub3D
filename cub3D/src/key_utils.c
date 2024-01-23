/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:32:15 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/18 20:46:54 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
	if (!window->keys.left && keycode == 65361)
		window->keys.left = true;
	if (!window->keys.right && keycode == 65363)
		window->keys.right = true;
	return (0);
}