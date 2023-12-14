/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:38:31 by asalic            #+#    #+#             */
/*   Updated: 2023/12/14 14:16:53 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

//If value == SPACE : check if around him, there is only 1 or SPACE or limits of the map
int     is_contour(int x, int y, char **map, t_data *data)
{
	if (x < data->ptr.width && y < data->ptr.height && map[y][x] && map[y][x] != '1' \
	&& map[y][x] != ' ')
	{
		ft_printf("x : %d, y : %d\n", x, y);
		return (1);
	}
	ft_printf("je renvoie 0\n");
	return (0);
}

int	space_check(t_data *data, char **map)
{
	if (is_contour(data->x-1, data->y+1, map, data) == 1)
	{
		ft_printf("je suis laaaaa 1\n");
		return (1);
	}
	if (is_contour(data->x-1, data->y, map, data) == 1)
	{
		ft_printf("je suis laaaaa 2\n");
		return (1);
	}
	if (is_contour(data->x-1, data->y-1, map, data) == 1)
	{
		ft_printf("je suis laaaaa3\n");
		return (1);
	}
	if (is_contour(data->x, data->y+1, map, data) == 1)
	{
		ft_printf("je suis laaaaa4\n");
		return (1);
	}
	if (is_contour(data->x, data->y-1, map, data) == 1)
	{
		ft_printf("je suis laaaaa5\n");
		return (1);
	}
	if (is_contour(data->x+1, data->y+1, map, data) == 1)
	{
		ft_printf("je suis laaaaa6\n");
		return (1);
	}
	if (is_contour(data->x+1, data->y, map, data) == 1)
	{
		ft_printf("je suis laaaaa7\n");
		return (1);
	}
	if (is_contour(data->x+1, data->y-1, map, data) == 1)
	{
		ft_printf("je suis laaaaa8\n");
		return (1);
	}
	return (0);
}

//Pour l'instant, part du principe que la map est rectangle, mais gere les spaces
int	main_parse(char **map, t_data *data)
{
	data->y = 0;
	while (map[data->y] && data->y < data->ptr.height)
	{
		data->x = 0;
		while (map[data->y][data->x] && data->x < data->ptr.width)
		{
			if (data->y == 0 || data->y == data->ptr.height -1 || data->x == 0
			|| data->x == data->ptr.width -1)
			{
				if (map[data->y][data->x] != '1' && map[data->y][data->x] != ' ')
				{
					return (1);
				}
				if (map[data->y][data->x] == ' ')
				{
					if (space_check(data, map) == 1)
					{
						ft_printf("je suis laaaaa\n");
						return (1);
					}
				}
			}
			data->x ++;
		}
		data->y ++;
	}
	ft_printf("right here ?");
	return (0);
}

