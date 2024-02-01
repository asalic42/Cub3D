/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_ennemy_n_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:12:59 by asalic            #+#    #+#             */
/*   Updated: 2024/01/30 15:50:55 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

static void	ennemy_player_found(t_parse_ennemy *enmy, int x, int y, char **map)
{
	if (map[y][x] == 'B')
	{
		enmy->bad_posx[enmy->i] = x;
		enmy->bad_posy[enmy->i] = y;
		enmy->ennemies ++;
		enmy->i ++;
	}
	if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || \
	map[y][x] == 'W')
	{
		enmy->play_posx = x;
		enmy->play_posy = y;
	}
}

void	pos_ennemy_player(t_parse_ennemy *enmy, char **map)
{
	int	x;
	int	y;

	y = 0;
	enmy->i = 0;
	enmy->ennemies = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			ennemy_player_found(enmy, x, y, map);
			x ++;
		}
		y ++;
	}
}
