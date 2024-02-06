/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:20:04 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 16:17:33 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	draw_squares(t_window *window, t_minimap *mini, t_map *map,
	t_player_pos *player)
{
	while (++mini->i < (int)player->x + 9)
	{
		mini->my = mini->j * map->x + mini->i;
		if (mini->j < 0 || mini->j > map->y - 1|| mini->i < 0 || mini->i > map->x - 1)
		{
			draw_line(init_rectangle(mini->cptr_x, mini->cptr_y, mini->cptr_x \
				+ 14, mini->cptr_y + 16), window->img_ptr, GREY, 0);
		}
		else if (mini->i >= 0 && mini->j >= 0 && mini->i < map->x && \
			mini->i == (int)player->x && mini->j == (int)player->y)
			draw_line(init_rectangle(mini->cptr_x, mini->cptr_y, mini->cptr_x
					+ 14, mini->cptr_y + 16), window->img_ptr, W, 0);
		else if (mini->i >= 0 && mini->j >= 0 && mini->i < map->x && \
		map->map[mini->my] == 1)
			draw_line(init_rectangle(mini->cptr_x, mini->cptr_y, mini->cptr_x
					+ 14, mini->cptr_y + 16), window->img_ptr, WALL, 0);
		else if (mini->i >= 0 && mini->j >= 0 && mini->i < map->x && \
		map->map[mini->my] == 3)
			draw_line(init_rectangle(mini->cptr_x, mini->cptr_y, mini->cptr_x
					+ 14, mini->cptr_y + 16), window->img_ptr, O_D, 0);
		else if (mini->i >= 0 && mini->j >= 0 && mini->i < map->x && \
		map->map[mini->my] == 4)
			draw_line(init_rectangle(mini->cptr_x, mini->cptr_y, mini->cptr_x
					+ 14, mini->cptr_y + 16), window->img_ptr, C_D, 0);
		else
			draw_line(init_rectangle(mini->cptr_x, mini->cptr_y, mini->cptr_x
					+ 14, mini->cptr_y + 16), window->img_ptr, GREY, 0);
		mini->cptr_x += 17;
	}
}

void	draw_map(t_window *window, t_player_pos	*player, t_map *map)
{
	t_minimap	minimap;

	draw_line(init_rectangle(0, 0, 287, 153), window->img_ptr, 0x888888, 0);
	minimap.j = (int)player->y - 5;
	minimap.cptr_y = 0;
	while (++minimap.j < (int)player->y + 5)
	{
		minimap.i = (int)player->x - 9;
		minimap.cptr_x = 0;
		draw_squares(window, &minimap, map, player);
		minimap.cptr_y += 17;
	}
	minimap.line = init_line(144, 75, 145 + (int)(player->dx * 300),
			80 + (int)(player->dy * 300));
	minimap.line.width = 2;
	draw_line(minimap.line, window->img_ptr, 0x00DD00, 0);
}
