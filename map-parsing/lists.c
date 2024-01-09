/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:03:04 by asalic            #+#    #+#             */
/*   Updated: 2024/01/09 15:18:37 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

//Transform map into list
t_listmap	*create_arg(int x, int y, int value)
{
	t_listmap	*new_arg;

	new_arg = ft_malloc(sizeof(t_listmap));
	if (!new_arg)
		return (free_garbage(), NULL);
	new_arg->value = value;
	new_arg->x = x;
	new_arg->y = y;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	return (new_arg);
}

void	add_arg(t_listmap **list, int x, int y, int value)
{
	t_listmap	*new_arg;
	t_listmap	*current;

	new_arg = create_arg(x, y, value);
	if (!new_arg)
		return ;
	if (*list == NULL)
		*list = new_arg;
	else
	{
		current = *list;
		while (current->next != NULL)
		{
			current->prev = current;
			current = current->next;
		}
		current->next = new_arg;
	}
}

int	is_good_map(t_listmap *list, char *map)
{
	int		fd;
	char	*buff;
	int		x;
	int		y;

	fd = open(map, O_RDONLY);
	buff = get_next_line(fd);
	x = 0;
	y = 0;
	while (buff)
	{
		while (buff[x] && buff[x] != '\n')
		{
			add_arg(&list, x, y, buff[x]);
			x ++;
		}
		buff = get_next_line(fd);
		x = 0;
		y++;
	}
	close(fd);
	print_list(list);
	return (0);
}

void	print_list(t_listmap *list)
{
	while (list)
	{
		ft_printf(" [%c]", list->value);
		if (list->x == 5)
			ft_printf("\n");
		list = list->next;
	}
}
