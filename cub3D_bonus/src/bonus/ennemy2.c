/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:48:34 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 16:17:09 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

int	comparator(const void *p, const void *p2)
{
	return (((t_ennemy *)p)->dist_to_player < ((t_ennemy *)p2)->dist_to_player);
}

int	size_of_array(t_window *window)
{
	return (sizeof(window->ennemies) / sizeof(*window->ennemies)
		/ 20 * window->ennemies_count);
}
