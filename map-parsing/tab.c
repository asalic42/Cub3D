/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:55:21 by asalic            #+#    #+#             */
/*   Updated: 2023/12/21 16:55:43 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

//Transform the map into tab
char	*go_map(t_parse *put, t_data *data)
{
	char	*tab;
	int		x;

	x = 0;
	tab = ft_malloc((data->ptr.width +1) * sizeof(char));
	if (!tab)
	{
		close_wndo(data);
		return (NULL);
	}
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
char	**ft_maptab(char *map, t_data *data)
{
	t_parse		put;
	int			y;
	char		**realmap;

	put.fd = open(map, O_RDONLY);
	realmap = ft_malloc((data->ptr.height * data->ptr.width +1) * \
	sizeof(char *));
	if (!realmap)
	{
		close_wndo(data);
		return (NULL);
	}
	y = 0;
	while (y < data->ptr.height)
	{
		realmap[y] = go_map(&put, data);
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
