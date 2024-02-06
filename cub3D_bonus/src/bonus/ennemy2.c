/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:48:34 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 18:20:17 by rciaze           ###   ########.fr       */
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

void	ennemy_animation(t_window *window)
{
	static int	cmpt;
	int			i;
	
	if (!cmpt)
		cmpt = 1;
	i = -1;
	cmpt++;
	if (cmpt == 10)
	{
		int i = -1;
		while (++i < window->ennemies_count)
			if (!window->ennemies[i].is_ded)
				window->ennemies[i].tex = &get_textures_instance()->xpm_ennemy_animated;
	}
	if (cmpt == 20)
	{
		while (++i < window->ennemies_count)
			if (!window->ennemies[i].is_ded)
				window->ennemies[i].tex = &get_textures_instance()->xpm_ennemy;
		cmpt = 1;
	}
}