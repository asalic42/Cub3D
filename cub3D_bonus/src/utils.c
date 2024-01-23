/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:36:44 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/18 20:44:38 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void	find_player_dir(t_player_pos *player, char dir)
{
	if (dir == 'N')
		player->a = PI3;
	else if (dir == 'E')
		player->a = 0;
	else if (dir == 'S')
		player->a = PI2;
	else if (dir == 'W')
		player->a = PI;
}

void	find_player(t_map *map, t_player_pos *player, char **char_map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (char_map[y][x] == 'N' || char_map[y][x] == 'E'
				|| char_map[y][x] == 'W' || char_map[y][x] == 'S')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				find_player_dir(player, char_map[y][x]);
				return ;
			}
			x ++;
		}
		y ++;
	}
}