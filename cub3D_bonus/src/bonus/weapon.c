/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:13:32 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 18:24:23 by rciaze           ###   ########.fr       */
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

void	print_weapon(t_window *window, t_texture_details *xpm, int j)
{
	int				x;
	int				y;
	char			*pixel;
	unsigned int	*value;
	int				i;

	x = 830;
	while (++j < xpm->width * 2)
	{
		y = 556;
		i = -1;
		while (++i < xpm->height * 2)
		{
			value = xpm->xpm_data + (i / 2 * xpm->width + j / 2) * 4;
			if (*value != 0x00FF00)
			{
				pixel = window->img_data + (y * (WIDTH) + x) * 4;
				*(unsigned int *)pixel = *value;
				*(unsigned int *)(pixel + 4) = *value;
			}
			y ++;
		}
		x ++;
	}
}

int	is_on_ennemy(float my, float mx, t_window *window)
{
	int	j;

	j = -1;
	while (++j < window->ennemies_count)
		if ((int)(mx) == (int)(window->ennemies[j].x) && (int)(my) == \
			(int)(window->ennemies[j].y))
			return (j + 1);
	return (0);
}

void	shot_fired(t_window *window, t_player_pos *player, t_map *map, \
	t_textures_path *tex)
{
	int				mp;
	int				mx;
	int				my;
	int				j;
	int				i;

	my = (int)player->y;
	mx = (int)player->x;
	mp = (int)(my * map->x + mx);
	window->anim_bool = true;
	j = 0;
	while (mp > 0 && mp < map->mp && map->map[mp] != 1 && map->map[mp] != 3)
	{
		j++;
		mx = (int)(player->x + (j * player->dx));
		my = (int)(player->y + (j * player->dy));
		mp = my * map->x + mx;
		i = is_on_ennemy(my, mx, window);
		if (i)
		{
			window->ennemies[i - 1].tex = &tex->xpm_ennemy_dead;
			window->ennemies[i - 1].is_ded = true;
			break ;
		}
	}
}
