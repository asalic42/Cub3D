/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:20:04 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/25 19:17:13 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	draw_squares_loop(t_window *window, t_minimap *mini, t_map *map)
{
	if (map->map[mini->j * map->x + mini->i] == 1)
		draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
				(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
			window->img_ptr, 0x555555, 0);
	else if (map->map[mini->j * map->x + mini->i] == 3)
		draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
				(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
			window->img_ptr, 0x3333FF, 0);
	else if (map->map[mini->j * map->x + mini->i] == 4)
		draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
				(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
			window->img_ptr, 0x7777CC, 0);
}

void	draw_squares(t_window *window, t_minimap *mini, t_map *map,
	t_player_pos *player)
{
	while (++mini->i < (int)player->x + 10)
	{
		if (mini->i >= 0 && mini->j >= 0 && mini->i < map->x && \
		mini->j < map->y && mini->i == (int)player->x && mini->j == \
		(int)player->y)
			draw_line(init_rectangle(mini->cptr_x * 18, mini->cptr_y * 18,
					(mini->cptr_x + 1) * 18 - 3, (mini->cptr_y + 1) * 18 - 1),
				window->img_ptr, 0xFFFFFF, 0);
		else if (mini->i >= 0 && mini->j >= 0 && mini->i < map->x && \
		mini->j < map->y && map->map && map->map[mini->j * map->x + mini->i])
			draw_squares_loop(window, mini, map);
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
