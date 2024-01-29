/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ennemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:14:19 by asalic            #+#    #+#             */
/*   Updated: 2024/01/29 19:02:21 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
void	print_map_color(char **map, int x, int y);

void	ennemy_init(t_window *window, t_parse_ennemy *enmy, char **map)
{
	enmy->ennemies = 0;
	enmy->play_posx = 0;
	enmy->play_posy = 0;
	enmy->savex = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(int));
    enmy->savey = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(int));
	enmy->cross_count = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(char));
	enmy->from_pass = ft_malloc((window->data.ptr.width * window->data.ptr.height +1) * sizeof(char));
	// enmy->bad_posx = ft_malloc(11 *sizeof(int));
	// enmy->bad_posy = ft_malloc(11 *sizeof(int))i
	enmy->map = ft_strdup_double(map);
}

int		ennemy_parse(char **map, t_window *window)
{
    t_parse_ennemy    enmy;

	ennemy_init(window, &enmy, map);
	pos_ennemy_player(&enmy);
	if (!ennemy_parse_loop(map, &enmy))
		return (0);
	return (1);
}

void	pos_ennemy_player(t_parse_ennemy *enmy)
{
	int	x;
	int	y;
	int i;

	y = 0;
	i = 0;
	while (enmy->map[y])
	{
		x = 0;
		while (enmy->map[y][x])
		{
			if (enmy->map[y][x] == 'B')
			{
				printf("x = %d and y = %d\n", x, y);
				enmy->bad_posx[i] = x;
				enmy->bad_posy[i] = y;
				enmy->ennemies ++;
				i ++;
			}
			if (enmy->map[y][x] == 'N' || enmy->map[y][x] == 'S' || enmy->map[y][x] == 'E' || \
			enmy->map[y][x] == 'W')
			{
				enmy->play_posx = x;
				enmy->play_posy = y;
			}
			x ++;
		}
		y ++;
	}
	// printf("badx : %d |  bady : %d\n", enmy->bad_posx[1], enmy->bad_posy[1]);
}

int	ennemy_parse_loop(char **map, t_parse_ennemy *enmy)
{
	int			i;
	int			x;
	int			y;
	
	i = 0;
	while (enmy->ennemies > 0)
	{
		if (!parsing_ennemy(enmy))
			return (0);
		enmy->ennemies --;
		while (enmy->cross_count[i])
		{
			enmy->cross_count[i] = '\0';
			enmy->from_pass[i] = '\0';
			enmy->savex[i] = '\0';
			enmy->savey[i] = '\0';
			i ++;
		}
		enmy->crosspass = 0;
		enmy->dir = 0;
		enmy->x = 0;
		enmy->y = 0;
		x =0;
		y=0;
		while (enmy->map[y])
		{
			while (enmy->map[y][x])
			{
				enmy->map[y][x] = '\0';
				x ++;
			}
			y ++;
		}
		enmy->map = ft_strdup_double(map);
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

int	is_cross_pass(int x, int y, t_parse_ennemy *enmy, char dir)
{
	if (enmy->map[y] && enmy->map[y][x] && (enmy->map[y][x] == 'N' || enmy->map[y][x] == 'S' || enmy->map[y][x] == 'E' || \
		enmy->map[y][x] == 'W'))
		return (0);
	if (enmy->map[y][x] && enmy->map[y][x] != '1' && enmy->dir != dir && is_already_pass(enmy, x, y))
		enmy->crosspass ++;
	return (1);
}

int	cross_pass(t_parse_ennemy *enmy)
{
	enmy->crosspass = 0;
	if (!is_cross_pass(enmy->x, enmy->y +1, enmy, 'n') || !is_cross_pass(enmy->x, enmy->y -1, enmy, 's') \
	|| !is_cross_pass(enmy->x +1, enmy->y, enmy, 'e') || !is_cross_pass(enmy->x -1, enmy->y, enmy, 'w'))
		return (0);
	return (1);
}

int	choose_path(t_parse_ennemy *enmy)
{
	if (enmy->map[enmy->y +1][enmy->x] != '1' && enmy->dir != 'n' && \
		is_already_pass(enmy, enmy->x, enmy->y +1))
		go_north(enmy);
	else if (enmy->map[enmy->y][enmy->x -1] != '1' && enmy->dir != 'w' && \
		is_already_pass(enmy, enmy->x -1, enmy->y))
		go_west(enmy);
	else if (enmy->map[enmy->y -1][enmy->x] != '1' && enmy->dir != 's' && \
		is_already_pass(enmy, enmy->x, enmy->y -1))
		go_south(enmy);
	else if (enmy->map[enmy->y][enmy->x +1] != '1' && enmy->dir != 'e' && \
		is_already_pass(enmy, enmy->x +1, enmy->y))
		go_east(enmy);
	else
	{
		if (!go_nowhere(enmy))
			return (0);
	}
	return (1);
}

int parsing_ennemy(t_parse_ennemy *enmy)
{
	enmy->i = 0;
	// printf("enmy->ennemies : %d\n", enmy->ennemies);
	enmy->y = enmy->bad_posy[enmy->ennemies -1];
	enmy->x = enmy->bad_posx[enmy->ennemies -1];
	// printf("x = %d et y = %d\n", enmy->x, enmy->y);
	while (enmy->ennemies > 0)
	{
		// printf("x = %d et y = %d\n", enmy->x, enmy->y);
		// printf("map = %c\n", enmy->map[enmy->y][enmy->x]);
		print_map_color(enmy->map, enmy->x, enmy->y);
		printf("\n");
		if (!cross_pass(enmy))
			return (1);
		else
		{
			if (!choose_path(enmy))
				return (0);
		}
	}
	return (1);
}

void	print_map_color(char **map, int x, int y)
{
	int	x1;
	int	y1;

	y1 = 0;
	while (map[y1])
	{
		x1 = 0;
		while (map[y1][x1])
		{
			if (x == x1 && y == y1)
				printf(RED"%c"NC, map[y1][x1]);
			else
				printf("%c", map[y1][x1]);
			x1 ++;
		}
		printf("\n");
		y1 ++;
	}
}
