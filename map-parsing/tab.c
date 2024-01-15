/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:55:21 by asalic            #+#    #+#             */
/*   Updated: 2024/01/15 18:20:42 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

//Transform the map into tab
char	*go_map(t_parse *put, t_data *data, t_window *window, int tour)
{
	char	*tab;
	int		x;

	x = 0;
	tab = ft_malloc((data->ptr.width +1) * sizeof(char));
	if (!tab)
	{
		destroy_window(window);
		return (NULL);
	}
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
	{
		destroy_window(window);
		return (NULL);
	}
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
	print_tab(realmap);
	return (realmap);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("{%s}\n", tab[i]);
		i ++;
	}
}

int	*simple_tab_int(char **char_map, t_window *window)
{
	int	*int_map;
	int	x;
	int	y;
	int	i;

	y = -1;
	i = 0;
	int_map = ft_malloc((window->data.ptr.height * window->data.ptr.width) * \
	sizeof(int));
	while (++y < window->data.ptr.height)
	{
		x = -1;
		while (++x < window->data.ptr.width)
		{
			if (char_map[y][x] == 'N' || char_map[y][x] == 'E' || \
			char_map[y][x] == 'W' || char_map[y][x] == 'S')
				int_map[i] = 2;
			else if (char_map[y][x] == ' ' || char_map[y][x] == '\0')
				int_map[i] = 0;
			else
				int_map[i] = char_map[y][x] - 48;
			i ++;
		}
	}
	return (int_map);
}
