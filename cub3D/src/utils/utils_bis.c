/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/02/06 16:36:16 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int	print_error(char *str)
{
	ft_printf("%s\n", str);
	return (0);
}

int	init_data(t_window *window, char *av)
{
	window->data.x = 0;
	window->data.y = 0;
	window->data.ptr.width = 0;
	window->data.ptr.height = countmap_y(av);
	if (!countmap_x(av, window))
		return (0);
	ft_maptab(av, &window->data, window);
	return (1);
}

int	is_in_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'W' && c != 'E'
		&& c != 'S' && c != ' ')
		return (0);
	return (1);
}

static int	in_loop_gnl(char *buf, int count)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
			i ++;
		if (buf[i] == 'N' || buf[i] == 'S' || buf[i] == 'W' \
		|| buf[i] == 'E' || buf[i] == 'F' || buf[i] == 'C')
		{
			count ++;
			break ;
		}
		else if (buf && buf[i] == '1')
			return (-2);
		else if (buf[i] && buf[i] != ' ' && buf[i] != '\t' && buf[i] \
		!= '\n')
			return (-1);
		i ++;
	}
	return (count);
}

/* Loop of gnl while it isn't the description of the map */
char	*loop_gnl(t_parse *parser)
{
	char	*buf;
	int		count;

	buf = get_next_line(parser->fd);
	count = 0;
	while (buf)
	{
		count = in_loop_gnl(buf, count);
		if (count == -2)
			return (buf);
		if (count > 6 || count == -1)
			return (NULL);
		buf = get_next_line(parser->fd);
	}
	return (buf);
}
