/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:21:28 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/29 10:38:38 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	compteur = 0;

clock_t						all_start;
clock_t						all_end;

float normalizeAngle(float angle) {
    while (angle < 0) angle += 2 * PI;
    while (angle >= 2 * PI) angle -= 2 * PI;
    return angle;
}

void	cast_ray(t_window *window)
{
	t_stuff_for_ray_casting		all_stuff;
	int							comp;
	t_textures_path				*textures;

	init_ray(&all_stuff, window);
	textures = get_textures_instance();
	all_stuff.r = -1;
	all_stuff.player = get_player_instance();
	while (++all_stuff.r < 960)
	{
		init_distances(&all_stuff);
		up_or_down(&all_stuff, window);
		find_closest_horizontal_intersection(&all_stuff, window);
		left_or_right(&all_stuff, window);
		find_closest_vertical_intersection(&all_stuff, window);
		comp = comp_distance(&all_stuff);
		all_stuff.lenght_tab[all_stuff.r] = (int)all_stuff.dist_t;
		calculate_line_height(&all_stuff, window);
		wich_texture(comp, textures, window, &all_stuff);
		increment_angle(&all_stuff);
	}
	float x_vector, y_vector;
	x_vector = window->ennemy.x - all_stuff.player->x;
	y_vector = window->ennemy.y - all_stuff.player->y;
	float lenght = sqrt(x_vector * x_vector + y_vector * y_vector);
	x_vector /= lenght;
	y_vector /= lenght;
	float target_angle = atan2(y_vector, x_vector);
	float relative_angle = target_angle - all_stuff.player->a;
	relative_angle = normalizeAngle(relative_angle) * 180/PI;
	if (relative_angle > 325 && relative_angle < 360)
		relative_angle -= 360;
	relative_angle *= -1;
	relative_angle += 35;
	relative_angle = 70 - relative_angle;
	int save = relative_angle * (960 / 70);
	if (relative_angle >= 0 && relative_angle <= 70)
	{
		float	dist = (distance(all_stuff.player->x, all_stuff.player->y, window->ennemy.x, window->ennemy.y));
		all_stuff.line_h = (HEIGHT) / dist;
		float texture_step = (float)textures->xpm_ennemy.height / all_stuff.line_h;
		int start_x, end_x;
		float position_x = 0;
		start_x = save * 2;
		end_x = start_x + all_stuff.line_h;
		if (start_x < 0)
		{
			position_x = texture_step * start_x;
			start_x += -start_x;
		}
		while (start_x < end_x && start_x < WIDTH)
		{
			if (dist < all_stuff.lenght_tab[start_x/2])
			{
				int		end_y, y;
				int		tex_x;
				int		tex_y;
				float	texture_position;
				y = (HEIGHT) / 2 - all_stuff.line_h / 2;
				end_y = y + all_stuff.line_h;
				tex_x = (int)(position_x);
				texture_position = 0;
				if (y < 0)
				{
					texture_position = texture_step * y;
					y += -y;
				}
				if (texture_position < 0)
					texture_position = 0;
				char		*value;
				char		*pixel;
				while (y < end_y && y < HEIGHT)
				{
					tex_y = (int)(texture_position);
			
					value = textures->xpm_ennemy.xpm_data
						+ (tex_y * textures->xpm_ennemy.width + tex_x) * (4);
					if (*(unsigned int *)value != 0x00FF00)
					{
						pixel = window->img_data + (y * (WIDTH) + start_x) * (4);
						*(unsigned int *)pixel = *(unsigned int *)value;
						*(unsigned int *)(pixel + 4) = *(unsigned int *)value;
					}
					texture_position += texture_step;
					y++;
				}
			}
			position_x += texture_step;
			start_x++;
		}
	}
	compteur++;
}

void	is_player_out_of_bouds(t_player_pos *player, t_window *window)
{
	(void)(window);

	if ((int)player->y > window->data.ptr.height)
		player->y = 1;
	else if ((int)player->y <= 0)
		player->y = (window->data.ptr.height - 1);
	else if ((int)player->x > window->data.ptr.width)
		player->x = 1;
	else if ((int)player->x <= 0)
		player->x = (window->data.ptr.width - 1);
}

/* A normer !!!! */
void	draw_player(t_window *window)
{	
	t_player_pos	*player;
	static	clock_t						start;
	static	clock_t						end;
	static	int							t_compteur = 0;
	static	t_line						ceilling;
	static	t_line						floor;

	player = get_player_instance();
	if (!ceilling.width)
		ceilling = init_rectangle(0, 0, (WIDTH), (HEIGHT) / 2);
	if (!floor.width)
		floor = init_rectangle(0, (HEIGHT) / 2, WIDTH, HEIGHT);
	draw_line(ceilling, window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->ceiling), 0);
	draw_line(floor, window->img_ptr,
		mlx_get_color_value(window->mlx_ptr, window->floor), 0);
	is_player_out_of_bouds(player, window);
	if (((double)(end - start) / CLOCKS_PER_SEC) > 1.5)
	{
		start = clock();
		t_compteur = 0;
	}
	cast_ray(window);
	
	end = clock();
	t_compteur++;
	int temps = 0;
	temps = (int)(t_compteur / ((double)(end - start) / CLOCKS_PER_SEC));

	draw_map(window, player, get_map_instance());
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
		window->img_ptr, 0, 0);
	char *str;
	str = ft_strjoin("Fps = ", ft_itoa(temps));
	mlx_string_put(window->mlx_ptr, window->win_ptr, 1800, 50, 0xFFFFFFFF, str);
	update_mlx_infos(window->mlx_ptr, window->win_ptr, window->img_ptr);
}

int	main(int ac, char **av)
{
	t_window	window;

	if (ac != 2)
		return (print_error(RED "Error : not enought args\n" NC));
	start_garbage();
	handle_error(&window, av[1]);
	if (!create_window(&window))
		return (0);
	update_mlx_infos(&window.mlx_ptr, &window.win_ptr, &window.img_ptr);
	init_textures(&window, "./textures/door.xpm");
	all_start = clock();
	initializer_audio(&window);
	window.win.mouse_x = 0;
	window.win.mouse_y = 0;
	window.ennemy.x = 41;
	window.ennemy.y = 12;
	pthread_create(&window.sound.audio, NULL, (void (*))play_music, &window);
	mlx_loop_hook(window.mlx_ptr, &move_player, &window);
	mlx_hook(window.win_ptr, 17, KeyPressMask, &destroy_window, &window);
	mlx_hook(window.win_ptr, KeyPress, 0, &key_press, &window);
	mlx_hook(window.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &window);
	mlx_loop(window.mlx_ptr);
	pthread_join(window.sound.audio, NULL);
	destroy_window(&window);
	return (1);
}
