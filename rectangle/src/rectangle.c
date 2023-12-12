/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:57:40 by rciaze            #+#    #+#             */
/*   Updated: 2023/10/19 15:57:57 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rectangle.h"

t_line	init_rectangle(int x1, int y1, int x2, int y2)
{
	t_line	rectangle;

	rectangle.x1 = x1;
	rectangle.y1 = (y1 + y2) / 2;
	rectangle.x2 = x2;
	rectangle.y2 = rectangle.y1;
	rectangle.width = ft_abs(y2 - y1);
	return (rectangle);
}
