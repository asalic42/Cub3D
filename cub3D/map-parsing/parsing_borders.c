/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_borders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 13:48:19 by asalic            #+#    #+#             */
/*   Updated: 2024/01/18 19:12:46 by asalic           ###   ########.fr       */
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
		if (!is_zero(data->y, map, data))
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
			if (!is_zero(data->y, map, data))
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
	if (data->x < data->ptr.width && map[y] && map[y][data->x] && \
	map[y][data->x] != '1' && map[y][data->x] != ' ')
		return (0);
	ft_printf("map = %s\n", map[y]);
	if (data->x -1 < data->ptr.width && map[y] && map[y][data->x -1] && \
	map[y][data->x -1] != '1' && map[y][data->x -1] != ' ')
		return (0);
	if (data->x +1 < data->ptr.width && map[y] && map[y][data->x +1] && \
	map[y][data->x +1] != '1' && map[y][data->x +1] != ' ')
		return (0);
	return (1);
}

/* Check if all element of the map are valid (1, 0, N/S/E/W) */
int	error_map(char *map)
{
	char	*check_line;
	int		len_player;
	t_parse	parser;
	int		i;

	parser.fd = open(map, O_RDONLY);
	len_player = -1;
	check_line = loop_gnl(&parser);
	while (check_line)
	{
		i = -1;
		while (check_line[++i] && check_line[i] != '\n')
		{
			if (!is_in_char(check_line[i]))
				return (print_error(RED "Error : forbidden element\n"NC));
			len_player = only_one_thing(check_line, i, len_player);
			if (len_player == 1)
				return (0);
		}
		check_line = get_next_line(parser.fd);
	}
	if (len_player == -1)
		return (print_error(RED "Error : no player detected\n" NC));
	close(parser.fd);
	return (1);
}

/* Check if there is only one player */
int	only_one_thing(char *check_line, int i, int len_player)
{
	if (check_line[i] == 'N' || check_line[i] == 'S' \
	|| check_line[i] == 'W' || check_line[i] == 'E')
	{
		if (len_player == -1)
			return (0);
		else
		{
			ft_printf(RED"Error : too much players detected in the map\n"NC);
			return (1);
		}
	}
	return (len_player);
}
