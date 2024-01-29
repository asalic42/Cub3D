/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ennemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:14:19 by asalic            #+#    #+#             */
/*   Updated: 2024/01/29 15:39:37 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
void	print_map_color(char **map, int x, int y);

int	pos_ennemy_player(char **map, t_window *window)
{
    t_parse_ennemy    enmy;
	char		**save_map;
	int	x;
	int	y;
	int i;

	y = 0;
	i = 0;
	enmy.ennemies = 0;
	enmy.play_posx = 0;
	enmy.play_posy = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'B')
			{
				enmy.bad_posx[i] = x;
				enmy.bad_posy[i] = y;
				enmy.ennemies ++;
				i ++;
			}
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || \
			map[y][x] == 'W')
			{
				enmy.play_posx = x;
				enmy.play_posy = y;
			}
			x ++;
		}
		y ++;
	}
	save_map = ft_strdup_double(map);
	while (enmy.ennemies > 0)
	{
		if (!parsing_ennemy(save_map, window, &enmy))
			return (0);
		enmy.ennemies --;
		save_map = ft_strdup_double(map);
	}
	return (1);
}

int	is_already_pass(t_parse_ennemy *enmy, int x, int y)
{
	int i;

	i = 0;
	while (enmy->savex[i])
	{
		if (x == enmy->savex[i] && y == enmy->savey[i])
			return (0);
		i ++;
	}
	return (1);
}

int	is_cross_pass(char **map, int x, int y, t_parse_ennemy *enmy, char dir)
{
	if (map[y] && map[y][x] && (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || \
		map[y][x] == 'W'))
		return (0);
	if (map[y][x] && map[y][x] != '1' && enmy->dir != dir && is_already_pass(enmy, x, y))
		enmy->crosspass ++;
	return (1);
}

int	cross_pass(char **map, t_parse_ennemy *enmy)
{
	enmy->crosspass = 0;
	if (!is_cross_pass(map, enmy->x, enmy->y +1, enmy, 'n') || !is_cross_pass(map, enmy->x, enmy->y -1, enmy, 's') \
	|| !is_cross_pass(map, enmy->x +1, enmy->y, enmy, 'e') || !is_cross_pass(map, enmy->x -1, enmy->y, enmy, 'w'))
		return (0);
	return (1);
}

int parsing_ennemy(char **map, t_window *window, t_parse_ennemy *enmy)
{
	int			i;

    enmy->savex = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(int));
    enmy->savey = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(int));
	enmy->cross_count = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(char));
	enmy->from_pass = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(char));
	i = 0;
	enmy->y = enmy->bad_posy[enmy->ennemies -1];
	enmy->x = enmy->bad_posx[enmy->ennemies -1];
	while (enmy->ennemies > 0)
	{
		// print_map_color(map, enmy->x, enmy->y);
		if (!cross_pass(map, enmy))
			return (1);
		else if (map[enmy->y +1][enmy->x] != '1' && enmy->dir != 'n' && is_already_pass(enmy, enmy->x, enmy->y +1))
		{
			if (enmy->crosspass > 1)
			{
				if (enmy->cross_count[i] != '\0')
					i ++;
				enmy->savex[i] = enmy->x;
				enmy->savey[i] = enmy->y;
				enmy->from_pass[i] = enmy->dir;
				enmy->cross_count[i] = 'n';
			}
			enmy->y ++;
			enmy->dir = 's';
		}
		else if (map[enmy->y][enmy->x -1] != '1' && enmy->dir != 'w' && is_already_pass(enmy, enmy->x -1, enmy->y))
		{
			if (enmy->crosspass > 1)
			{
				if (enmy->cross_count[i] != '\0')
					i ++;
				enmy->savex[i] = enmy->x;
				enmy->savey[i] = enmy->y;
				enmy->from_pass[i] = enmy->dir;
				enmy->cross_count[i] = 'w';
			}
			enmy->x --;
			enmy->dir = 'e';
		}
		else if (map[enmy->y -1][enmy->x] != '1' && enmy->dir != 's' && is_already_pass(enmy, enmy->x, enmy->y -1))
		{
			if (enmy->crosspass > 1)
			{
				if (enmy->cross_count[i] != '\0')
					i ++;
				enmy->savex[i] = enmy->x;
				enmy->savey[i] = enmy->y;
				enmy->from_pass[i] = enmy->dir;
				enmy->cross_count[i] = 's';
			}
			enmy->y --;
			enmy->dir = 'n';
		}
		else if (map[enmy->y][enmy->x +1] != '1' && enmy->dir != 'e' && is_already_pass(enmy, enmy->x +1, enmy->y))
		{
			if (enmy->crosspass > 1)
			{
				if (enmy->cross_count[i] != '\0')
					i ++;
				enmy->savex[i] = enmy->x;
				enmy->savey[i] = enmy->y;
				enmy->from_pass[i] = enmy->dir;
				enmy->cross_count[i] = 'e';
			}
			enmy->x ++;
			enmy->dir = 'w';
		}
		else
		{
			if (!enmy->cross_count[i])
				return (print_error("Error : Ennemy inaccessible\n"));
			enmy->x = enmy->savex[i];
			enmy->y = enmy->savey[i];
			if (enmy->cross_count[i] == 'n' || enmy->from_pass[i] == 'n')
				map[enmy->y +1][enmy->x] = '1';
			if (enmy->cross_count[i] == 's' || enmy->from_pass[i] == 's')
				map[enmy->y -1][enmy->x] = '1';
			if (enmy->cross_count[i] == 'e' || enmy->from_pass[i] == 'e')
				map[enmy->y][enmy->x +1] = '1';
			if (enmy->cross_count[i] == 'w' || enmy->from_pass[i] == 'w')
				map[enmy->y][enmy->x -1] = '1';
			enmy->savex[i] = '\0';
			enmy->savey[i] = '\0';
			enmy->cross_count[i] = '\0';
			enmy->dir = enmy->from_pass[i];
			enmy->from_pass[i] = '\0';
			i --;
		}
	}
	return (1);
}

// void	print_map_color(char **map, int x, int y)
// {
// 	int	x1;
// 	int	y1;

// 	y1 = 0;
// 	while (map[y1])
// 	{
// 		x1 = 0;
// 		while (map[y1][x1])
// 		{
// 			if (x == x1 && y == y1)
// 				printf(RED"%c"NC, map[y1][x1]);
// 			else
// 				printf("%c", map[y1][x1]);
// 			x1 ++;
// 		}
// 		printf("\n");
// 		y1 ++;
// 	}
// }
