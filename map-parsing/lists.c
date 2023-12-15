/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:03:04 by asalic            #+#    #+#             */
/*   Updated: 2023/12/15 15:20:11 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

//Transform map into list
t_listmap	*create_arg(int x, int y, int value)
{
	t_listmap	*new_arg;

	new_arg = ft_malloc(sizeof(t_listmap));
	if (!new_arg)
		return (NULL);
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

int     is_good_map(t_listmap *list, char *map)
{
    int     fd;
    char    *buff;
    int     x;
    int     y;
    
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
    print_list(list);
    return (0);
}

void    print_list(t_listmap *list)
{
    while (list)
    {
        ft_printf(" [%c]", list->value);
        if (list->x == 5)
            ft_printf("\n");
        list = list->next;
    }    
}
//Transform the map into tab
char	*go_map(t_parse *put, t_data *data)
{
	char	*tab;
	int		x=0;

	tab = ft_malloc((data->ptr.width +1) * sizeof(char));
	if (!tab)
        return (NULL);
	// close_wndow(data);
    put->buffer = get_next_line(put->fd);
    while (put->buffer && put->buffer[x] != '\n' && put->buffer[x] != '\0')
    {
        tab[x] = put->buffer[x];
        x ++;
    }
    tab[x] = '\0';
	return (tab);
}

//create the map in a char [x][y]
char	**ft_maptab(char *map, t_data *data)
{
	t_parse	    put;
	int			y;
	char		**realmap;

	put.fd = open(map, O_RDONLY);
	realmap = ft_malloc((data->ptr.height * data->ptr.width+1) * sizeof(char *));
	if (!realmap)
        return (NULL);
	// close_wndow(data);
	y = 0;
	while (y < data->ptr.height)
	{
		realmap[y] = go_map(&put, data);
		y ++;
	}
	realmap[y] = NULL;
	close(put.fd);
    print_tab(realmap);
	return (realmap);
}

void    print_tab(char **tab)
{
    int i=0;
    while (tab[i])
    {
        ft_printf("{%s}\n", tab[i]);
        i ++;
    }
}