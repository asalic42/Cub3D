/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/02/06 19:07:43 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

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

int	print_error(char *str)
{
	ft_printf(RED"%s\n"NC, str);
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

int	ft_double_len(char **str)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			count ++;
			j ++;
		}
		i ++;
	}
	return (count);
}
