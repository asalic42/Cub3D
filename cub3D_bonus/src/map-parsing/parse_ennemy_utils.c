/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ennemy_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:50:45 by asalic            #+#    #+#             */
/*   Updated: 2024/01/30 15:49:56 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int	is_already_pass(t_parse_ennemy *enmy, int x, int y)
{
	int	i;

	i = 0;
	while (enmy->savex[i])
	{
		if (x == enmy->savex[i] && y == enmy->savey[i])
			return (0);
		i ++;
	}
	return (1);
}

static int	is_cross_pass(int x, int y, t_parse_ennemy *enmy, char dir)
{
	if (enmy->map[y] && enmy->map[y][x] && (enmy->map[y][x] == 'N' || \
	enmy->map[y][x] == 'S' || enmy->map[y][x] == 'E' || \
	enmy->map[y][x] == 'W'))
		return (0);
	if (enmy->map[y][x] && enmy->map[y][x] != '1' && enmy->dir != dir \
	&& is_already_pass(enmy, x, y))
		enmy->crosspass ++;
	return (1);
}

int	cross_pass(t_parse_ennemy *enmy)
{
	enmy->crosspass = 0;
	if (!is_cross_pass(enmy->x, enmy->y +1, enmy, 'n') || \
	!is_cross_pass(enmy->x, enmy->y -1, enmy, 's') || \
	!is_cross_pass(enmy->x +1, enmy->y, enmy, 'e') || \
	!is_cross_pass(enmy->x -1, enmy->y, enmy, 'w'))
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
