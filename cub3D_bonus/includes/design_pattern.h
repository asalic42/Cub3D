/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_pattern.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:36:22 by raphael           #+#    #+#             */
/*   Updated: 2024/02/06 15:50:04 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESIGN_PATTERN_H
# define DESIGN_PATTERN_H

# include <time.h>

typedef struct s_fps
{
	clock_t	start;
	clock_t	end;
	int		t_compteur;
	int		compteur;
	char	*str;
}	t_fps;

typedef struct s_player_pos
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	a;
}	t_player_pos;

typedef struct s_map
{
	int		mp;
	int		mx;
	int		my;
	int		x;
	int		y;
	int		*map;
}	t_map;

typedef struct s_texture_details
{
	int				width;
	int				height;
	void			*xpm;
	void			*xpm_data;
}	t_texture_details;

typedef struct s_textures_path
{
	t_texture_details	xpm1;
	t_texture_details	xpm2;
	t_texture_details	xpm3;
	t_texture_details	xpm4;
	t_texture_details	xpm_door;
	t_texture_details	xpm_ennemy;
	t_texture_details	xpm_ennemy_animated;
	t_texture_details	xpm_ennemy_dead;
	t_texture_details	xpm_weapon;
	t_texture_details	xpm_weapon_firing1;
	t_texture_details	xpm_weapon_firing2;
	t_texture_details	xpm_weapon_firing3;
	t_texture_details	xpm_weapon_firing4;
	t_texture_details	xpm_weapon_firing5;
	t_texture_details	xpm_weapon_firing6;
}	t_textures_path;

t_map			*get_map_instance(void);
t_player_pos	*get_player_instance(void);
t_textures_path	*get_textures_instance(void);
t_fps			*get_fps_instance(void);
#endif
