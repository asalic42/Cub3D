/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:20:04 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/22 18:31:25 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	draw_squares(t_window *window, t_minimap *mini, t_map *map,
	t_player_pos *player)
{
	while (++mini->i < (int)player->x + 10)
	{
		if (mini->i == (int)player->x && mini->j == (int)player->y)
			draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
					(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
				window->img_ptr, 0xFFFFFF, 0);
		else if (map->map[mini->j * map->x + mini->i] == 1)
			draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
					(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
				window->img_ptr, 0xFF0000, 0);
		else
			draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
					(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
				window->img_ptr, 0xBBBBBB, 0);
		mini->cptr_x += 1;
	}
}

void	draw_map(t_window *window, t_player_pos	*player, t_map *map)
{
	t_minimap	minimap;

	draw_line(init_rectangle(0, 0, 337, 198), window->img_ptr, 0x888888, 0);
	minimap.j = (int)player->y - 6;
	minimap.cptr_y = 0;
	while (++minimap.j < (int)player->y + 6)
	{
		minimap.i = (int)player->x - 10;
		minimap.cptr_x = 0;
		draw_squares(window, &minimap, map, player);
		minimap.cptr_y++;
	}
	minimap.line = init_line(170, 98, 170 + (int)(player->dx * 500),
			98 + (int)(player->dy * 500));
	minimap.line.width = 2;
	draw_line(minimap.line, window->img_ptr, 0x00FF00, 0);
}
