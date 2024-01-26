/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ennemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:14:19 by asalic            #+#    #+#             */
/*   Updated: 2024/01/26 15:41:49 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	pos_ennemy_player(char **map, t_ennemy *enmy)
{
	int	x;
	int	y;
	int i;

	y = 0;
	i = 0;
	enmy->ennemies = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'B')
			{
				enmy->bad_posx[i] = x;
				enmy->bad_posy[i] = y;
				enmy->ennemies ++;
				i ++;
			}
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || \
			map[y][x] == 'W')
			{
				enmy->play_posx = x;
				enmy->play_posy = y;
			}
			x ++;
		}
		y ++;
	}
}

int	is_cross_pass(char **map, int x, int y, t_ennemy *enmy)
{
	if (map[y][x] != '1')
		enmy->crosspass ++;
	else if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || \
		map[y][x] == 'W')
		return (0);
	return (1);
}

int	cross_pass(char **map, t_ennemy *enmy)
{
	enmy->crosspass = 0;
	if (!is_cross_pass(map, enmy->x, enmy->y +1, enmy) || !is_cross_pass(map, enmy->x, enmy->y -1, enmy) \
	|| !is_cross_pass(map, enmy->x +1, enmy->y, enmy) || !is_cross_pass(map, enmy->x -1, enmy->y, enmy))
		return (1);
	return (1);
}

int parsing_ennemy(char **map, t_window *window)
{
    t_ennemy    enmy;
	int			i;
    
    enmy.savex = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(int));
    enmy.savey = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(int));
	enmy.cross_count = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(char));
    pos_ennemy_player(map, &enmy);
	i = 0;
	enmy.y = enmy.bad_posy[enmy.ennemies -1];
	enmy.x = enmy.bad_posx[enmy.ennemies -1];
	while (enmy.ennemies > 0)
	{
		if (!cross_pass(map, &enmy))
		{
			enmy.ennemies --;
			enmy.y = enmy.bad_posy[enmy.ennemies -1];
			enmy.x = enmy.bad_posx[enmy.ennemies -1];
		}
		else if (map[enmy.y+1][enmy.x] != '1' && enmy.dir != 'n')
		{
			if (enmy.crosspass > 1)
			{
				enmy.savex[i] = enmy.x;
				enmy.savey[i] = enmy.y;
				enmy.cross_count[i] = 'n';
				i ++;
			}
			enmy.y ++;
			enmy.dir = 's';
		}
		else if (map[enmy.y-1][enmy.x] != '1' && enmy.dir != 's')
		{
			if (enmy.crosspass > 1)
			{
				enmy.savex[i] = enmy.x;
				enmy.savey[i] = enmy.y;
				enmy.cross_count[i] = 's';
				i ++;
			}
			enmy.y --;
			enmy.dir = 'n';
		}
		else if (map[enmy.y][enmy.x+1] != '1' && enmy.dir != 'e')
		{
			if (enmy.crosspass > 1)
			{
				enmy.savex[i] = enmy.x;
				enmy.savey[i] = enmy.y;
				enmy.cross_count[i] = 'e';
				i ++;
			}
			enmy.x ++;
			enmy.dir = 'w';
		}
		else if (map[enmy.y][enmy.x-1] != '1' && enmy.dir != 'w')
		{
			if (enmy.crosspass > 1)
			{
				enmy.savex[i] = enmy.x;
				enmy.savey[i] = enmy.y;
				enmy.cross_count[i] = 'w';
				i ++;
			}
			enmy.x --;
			enmy.dir = 'e';
		}
		else
		{
			enmy.x = enmy.savex[i];
			enmy.y = enmy.savey[i];
			if (enmy.cross_count[i] == 'n')
				map[enmy.y +1][enmy.x] = '1';
			else if (enmy.cross_count[i] == 's')
				map[enmy.y -1][enmy.x] = '1';
			else if (enmy.cross_count[i] == 'e')
				map[enmy.y][enmy.x +1] = '1';
			else if (enmy.cross_count[i] == 'w')
				map[enmy.y][enmy.x -1] = '1';
			enmy.savex[i] = '\0';
			enmy.savey[i] = '\0';
			enmy.cross_count[i] = '\0';
			i --;
		}
	}
	return (1);
}