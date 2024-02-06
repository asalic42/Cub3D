/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:55:21 by asalic            #+#    #+#             */
/*   Updated: 2024/02/06 16:42:16 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

//Transform the map into tab
char	*go_map(t_parse *put, t_data *data, t_window *window, int tour)
{
	char	*tab;
	int		x;

	x = 0;
	tab = ft_malloc((data->ptr.width +1) * sizeof(char));
	if (!tab)
		destroy_window(window);
	if (tour == 1)
		put->buffer = loop_gnl(put);
	else
		put->buffer = get_next_line(put->fd);
	while (put->buffer && put->buffer[x] != '\n' && put->buffer[x] != '\0')
	{
		tab[x] = put->buffer[x];
		x ++;
	}
	while (x < data->ptr.width)
	{
		tab[x] = '\0';
		x++;
	}
	tab[x] = '\0';
	return (tab);
}

//create the map in a char [x][y]
char	**ft_maptab(char *map, t_data *data, t_window *window)
{
	t_parse		put;
	int			y;
	char		**realmap;

	put.fd = open(map, O_RDONLY);
	realmap = ft_malloc((data->ptr.height * data->ptr.width +1) * \
	sizeof(char *));
	if (!realmap)
		destroy_window(window);
	y = 0;
	while (y < data->ptr.height)
	{
		if (y == 0)
			realmap[y] = go_map(&put, data, window, 1);
		else
			realmap[y] = go_map(&put, data, window, 0);
		y ++;
	}
	realmap[y] = NULL;
	close(put.fd);
	data->ptr.map = realmap;
	return (realmap);
}

int	add_to_tab_int(char c)
{
	if (c == 'N' || c == 'E' || \
	c == 'W' || c == 'S')
		return (2);
	else if (c == 'D')
		return (3);
	else if (c == 'B')
		return (5);
	else if (c == ' ' || c == '\0')
		return (0);
	else
		return (c - 48);
}

int	*simple_tab_int(char **char_map, t_window *window, int y)
{
	int	*int_map;
	int	x;
	int	i;

	i = 0;
	int_map = ft_malloc((window->data.ptr.height * window->data.ptr.width) * \
	sizeof(int));
	window->ennemies_count = 0;
	while (++y < window->data.ptr.height)
	{
		x = -1;
		while (++x < window->data.ptr.width)
		{
			int_map[i] = add_to_tab_int(char_map[y][x]);
			if (int_map[i] == 5 && window->ennemies_count < 20)
			{
				window->ennemies[window->ennemies_count].x = x + 0.5;
				window->ennemies[window->ennemies_count].y = y + 0.5;
				window->ennemies_count++;
			}
			i ++;
		}
	}
	return (int_map);
}

int	error_cases(void)
{
	free_garbage();
	exit(EXIT_FAILURE);
}
