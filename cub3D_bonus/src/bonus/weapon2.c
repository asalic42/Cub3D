/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:17:30 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/07 11:29:28 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

void	if_s_weapon(int *w_cmpt, t_window *window)
{
	*w_cmpt += 1;
	if (*w_cmpt < 6)
		print_weapon(window, &get_textures_instance()->xpm_weapon_firing1, -1);
	else if (*w_cmpt < 12)
		print_weapon(window, &get_textures_instance()->xpm_weapon_firing2, -1);
	else if (*w_cmpt < 18)
		print_weapon(window, &get_textures_instance()->xpm_weapon_firing6, -1);
	else if (*w_cmpt < 24)
		print_weapon(window, &get_textures_instance()->xpm_weapon_firing4, -1);
	else if (*w_cmpt < 30)
		print_weapon(window, &get_textures_instance()->xpm_weapon_firing5, -1);
	else if (*w_cmpt < 36)
		print_weapon(window, &get_textures_instance()->xpm_weapon_firing6, -1);
	if (*w_cmpt > 36)
	{
		print_weapon(window, &get_textures_instance()->xpm_weapon, -1);
		if (window->end == window->ennemies_count)
		{
			printf(CYAN"\tYOU WIN\n\n"NC);
			destroy_window(window);
		}
		*w_cmpt = -1;
	}
}

void	weapon_animation(t_window *window)
{
	static int		w_cmpt;

	if (!w_cmpt)
		w_cmpt = -1;
	if (window->anim_bool)
	{
		window->anim_bool = false;
		w_cmpt = 1;
	}		
	if (w_cmpt > 0)
		if_s_weapon(&w_cmpt, window);
	else
		print_weapon(window, &get_textures_instance()->xpm_weapon, -1);
}
