/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/01/23 18:27:47 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

/* Loop of gnl while it isn't the description of the map */
char	*loop_gnl(t_parse *parser)
{
	int		i;
	char	*buf;

	i = 0;
	buf = get_next_line(parser->fd);
	while (buf)
	{
		i = 0;
		while (buf[i])
		{
			while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
				i ++;
			if (buf[i] == 'N' || buf[i] == 'S' || buf[i] == 'W' \
			|| buf[i] == 'E' || buf[i] == 'F' || buf[i] == 'C')
				break ;
			else if (buf && buf[i] == '1')
				return (buf);
			i ++;
		}
		buf = get_next_line(parser->fd);
	}
	return (buf);
}

int	print_error(char *str)
{
	ft_printf("%s\n", str);
	return (0);
}

void	init_data(t_window *window, char *av)
{
	window->data.x = 0;
	window->data.y = 0;
	window->data.ptr.width = 0;
	window->data.ptr.height = countmap_y(av);
	countmap_x(av, window);
	ft_maptab(av, &window->data, window);
}
