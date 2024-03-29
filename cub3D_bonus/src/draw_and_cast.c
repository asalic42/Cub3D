/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_cast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:05:22 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/07 12:57:39 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cast_ray(t_window *window)
{
	t_stuff_for_ray_casting		all_stuff;
	int							comp;
	t_textures_path				*textures;
	t_fps						*fps;

	fps = get_fps_instance();
	init_ray(&all_stuff, window);
	textures = get_textures_instance();
	all_stuff.r = 300 / (WIDTH / NB_OF_STRIPES) - 1;
	all_stuff.player = get_player_instance();
	while (++all_stuff.r < (NB_OF_STRIPES - 300) / (WIDTH / NB_OF_STRIPES))
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff, window);
		find_closest_horizontal_intersection(&all_stuff, window);
		left_or_right(&all_stuff, window);
		find_closest_vertical_intersection(&all_stuff, window);
		comp = comp_distance(&all_stuff, 0);
		all_stuff.lenght_tab[all_stuff.r] = all_stuff.line_h;
		calculate_line_height(&all_stuff, window);
		wich_texture(comp, textures, window, &all_stuff);
		increment_angle(&all_stuff);
	}
	ennemy(textures, &all_stuff, window);
	fps->compteur++;
}

/* Count the number of the ennemies left in the map */
static void	count_ennemies_left(t_window *win)
{
	char	*count_ennemy;

	count_ennemy = ft_strjoin("Ennemies left : ", \
		ft_itoa(win->ennemies_count - win->end));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 1800, 100, 0xFFFFFF, \
		count_ennemy);
}

/* Count the number of fps and animate ennemies and the weapon */
void	draw_and_count_fps(t_player_pos *player, t_window *win)
{
	t_fps			*fps;
	int				temps;

	fps = get_fps_instance();
	if (((double)(fps->end - fps->start) / CLOCKS_PER_SEC) > 1.5)
	{
		fps->start += ((double)(fps->end - fps->start)) / 2;
		fps->t_compteur /= 2;
	}
	cast_ray(win);
	fps->end = clock();
	fps->t_compteur++;
	temps = 0;
	temps = (int)(fps->t_compteur / ((double)(fps->end - fps->start)
				/ CLOCKS_PER_SEC));
	draw_map(win, player, get_map_instance());
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr,
		win->img_ptr, 0, 0);
	fps->str = ft_strjoin("Fps = ", ft_itoa(temps));
	ennemy_animation(win);
	weapon_animation(win);
	count_ennemies_left(win);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 1800, 50, 0xFFFFFF, fps->str);
}

void	draw_player(t_window *window)
{	
	t_player_pos	*player;
	static t_line	ceilling;
	static t_line	floor;

	player = get_player_instance();
	if (!ceilling.width)
		ceilling = init_rectangle(300, 150, (WIDTH) - 300, (HEIGHT) / 1.9);
	if (!floor.width)
		floor = init_rectangle(300, (HEIGHT) / 1.9, WIDTH - 300, HEIGHT - 150);
	draw_line(ceilling, window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->ceiling), 0);
	draw_line(floor, window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->floor), 0);
	is_player_out_of_bouds(player, window);
	draw_and_count_fps(player, window);
	update_mlx_infos(window->mlx_ptr, window->win_ptr, window->img_ptr);
}
