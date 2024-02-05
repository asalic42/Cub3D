/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/02/05 18:29:43 by asalic           ###   ########.fr       */
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
