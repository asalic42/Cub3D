/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:14:04 by asalic            #+#    #+#             */
/*   Updated: 2024/01/30 15:53:29 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	go_north(t_parse_ennemy *enmy)
{
	if (enmy->crosspass > 1)
	{
		if (enmy->cross_count[enmy->i] != '\0')
			enmy->i ++;
		enmy->savex[enmy->i] = enmy->x;
		enmy->savey[enmy->i] = enmy->y;
		enmy->from_pass[enmy->i] = enmy->dir;
		enmy->cross_count[enmy->i] = 'n';
	}
	enmy->y ++;
	enmy->dir = 's';
}

void	go_west(t_parse_ennemy *enmy)
{
	if (enmy->crosspass > 1)
	{
		if (enmy->cross_count[enmy->i] != '\0')
			enmy->i ++;
		enmy->savex[enmy->i] = enmy->x;
		enmy->savey[enmy->i] = enmy->y;
		enmy->from_pass[enmy->i] = enmy->dir;
		enmy->cross_count[enmy->i] = 'w';
	}
	enmy->x --;
	enmy->dir = 'e';
}

void	go_south(t_parse_ennemy *enmy)
{
	if (enmy->crosspass > 1)
	{
		if (enmy->cross_count[enmy->i] != '\0')
			enmy->i ++;
		enmy->savex[enmy->i] = enmy->x;
		enmy->savey[enmy->i] = enmy->y;
		enmy->from_pass[enmy->i] = enmy->dir;
		enmy->cross_count[enmy->i] = 's';
	}
	enmy->y --;
	enmy->dir = 'n';
}

void	go_east(t_parse_ennemy *enmy)
{
	if (enmy->crosspass > 1)
	{
		if (enmy->cross_count[enmy->i] != '\0')
			enmy->i ++;
		enmy->savex[enmy->i] = enmy->x;
		enmy->savey[enmy->i] = enmy->y;
		enmy->from_pass[enmy->i] = enmy->dir;
		enmy->cross_count[enmy->i] = 'e';
	}
	enmy->x ++;
	enmy->dir = 'w';
}

int	go_nowhere(t_parse_ennemy *enmy)
{
	if (!enmy->cross_count[enmy->i])
		return (print_error("Error : Ennemy inaccessible\n"));
	enmy->x = enmy->savex[enmy->i];
	enmy->y = enmy->savey[enmy->i];
	if (enmy->cross_count[enmy->i] == 'n' || enmy->from_pass[enmy->i] == 'n')
		enmy->map[enmy->y +1][enmy->x] = '1';
	if (enmy->cross_count[enmy->i] == 's' || enmy->from_pass[enmy->i] == 's')
		enmy->map[enmy->y -1][enmy->x] = '1';
	if (enmy->cross_count[enmy->i] == 'e' || enmy->from_pass[enmy->i] == 'e')
		enmy->map[enmy->y][enmy->x +1] = '1';
	if (enmy->cross_count[enmy->i] == 'w' || enmy->from_pass[enmy->i] == 'w')
		enmy->map[enmy->y][enmy->x -1] = '1';
	enmy->savex[enmy->i] = '\0';
	enmy->savey[enmy->i] = '\0';
	enmy->cross_count[enmy->i] = '\0';
	enmy->dir = enmy->from_pass[enmy->i];
	enmy->from_pass[enmy->i] = '\0';
	enmy->i --;
	return (1);
}
