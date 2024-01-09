/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_borders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:19 by asalic            #+#    #+#             */
/*   Updated: 2024/01/09 15:18:45 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	first_line(t_data *data, char **map)
{
	if (data->y == 0 && ((map[data->y][data->x] != '\0' \
	&& (map[data->y][data->x] != '1' && map[data->y][data->x] != ' ')) \
	&& map[data->y +1][data->x] != '1'))
		return (print_error(RED"Error : wrong up borders\n"NC));
	else if (data->y == 0 && !map[data->y][data->x])
	{
		if (!is_zero(data->y +1, map, data))
			return (print_error(RED"Error : wrong borders\n"NC));
	}
	return (1);
}

int	map_up_n_down(char **map, t_data *data)
{
	while (data->y < data->ptr.height)
	{
		if (!first_line(data, map))
			return (0);
		if (data->y == data->ptr.height -1 && ((map[data->y][data->x] != '\0' \
		&& (map[data->y][data->x] != '1' && map[data->y][data->x] != ' ')) \
		&& map[data->y -1][data->x] != '1'))
			return (print_error(RED"Error : wrong down borders\n"NC));
		else if (data->y == data->ptr.height -1 && !map[data->y][data->x])
		{
			if (!is_zero(data->y -1, map, data))
				return (print_error(RED"Error : wrong borders\n"NC));
		}
		data->x ++;
		if (data->x == data->ptr.width -1)
		{
			data->x = 0;
			if (data->y == 0)
				data->y = data->ptr.height -1;
			else
				data->y = data->ptr.height;
		}
	}
	return (1);
}

int	is_zero(int y, char **map, t_data *data)
{
	if (data->x < data->ptr.width && map[y][data->x] && \
	map[y][data->x] != '1' && map[y][data->x] != ' ')
		return (0);
	if (data->x -1 < data->ptr.width && map[y][data->x -1] && \
	map[y][data->x -1] != '1' && map[y][data->x -1] != ' ')
		return (0);
	if (data->x +1 < data->ptr.width && map[y][data->x +1] && \
	map[y][data->x +1] != '1' && map[y][data->x +1] != ' ')
		return (0);
	return (1);
}
