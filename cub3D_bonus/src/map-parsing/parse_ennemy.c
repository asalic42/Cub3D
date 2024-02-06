/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ennemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:14:19 by asalic            #+#    #+#             */
/*   Updated: 2024/02/06 09:55:56 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	ennemy_init(t_window *window, t_parse_ennemy *enmy)
{
	enmy->i = 0;
	enmy->dir = 0;
	enmy->crosspass = 0;
	enmy->savex = ft_calloc((window->data.ptr.width * window->data.ptr.height \
		+1), sizeof(int));
	enmy->savey = ft_calloc((window->data.ptr.width * window->data.ptr.height \
	+1), sizeof(int));
	enmy->cross_count = ft_calloc((window->data.ptr.width * \
	window->data.ptr.height +1), sizeof(char));
	enmy->from_pass = ft_calloc((window->data.ptr.width * \
	window->data.ptr.height +1), sizeof(char));
}

int	ennemy_parse(char **map, t_window *window)
{
	t_parse_ennemy	enmy;

	pos_ennemy_player(&enmy, map);
	if (enmy.ennemies > 20)
		return (print_error("Error : too many ennemies (max : 20)\n"));
	if (!ennemy_parse_loop(map, &enmy, window))
		return (0);
	return (1);
}

int	ennemy_parse_loop(char **map, t_parse_ennemy *enmy, t_window *window)
{
	while (enmy->ennemies > 0)
	{
		if (!parsing_ennemy(enmy, map, window))
			return (0);
		enmy->ennemies --;
	}
	return (1);
}

int	parsing_ennemy(t_parse_ennemy *enmy, char **map, t_window *window)
{
	ennemy_init(window, enmy);
	enmy->map = ft_strdup_double(map);
	enmy->y = enmy->bad_posy[enmy->ennemies -1];
	enmy->x = enmy->bad_posx[enmy->ennemies -1];
	while (enmy->ennemies > 0)
	{
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
