/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:36:44 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/18 20:19:43 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	key_press_2(t_window *window)
{
	t_player_pos *player = get_player_instance();
	if (window->keys.left)
	{
		player->a -= 0.03;
		if (player->a < 0)
			player->a += 2 * PI;
		player->dx = cos(player->a) * 0.08;
		player->dy = sin(player->a) * 0.08;
	}
	if (window->keys.right)
	{
		player->a += 0.03;
		if (player->a > 2 * PI)
			player->a -= 2 * PI;
		player->dx = cos(player->a) * 0.08;
		player->dy = sin(player->a) * 0.08;
	}
	if (window->keys.w)
	{
		if (window->keys.a || window->keys.d)
		{
			player->x += player->dx / 1.5;
			player->y += player->dy / 1.5;	
		}
		else
		{
			player->x += player->dx;
			player->y += player->dy;
		}
	}
	if (window->keys.s)
	{
		if (window->keys.a || window->keys.d)
		{
			player->x -= player->dx / 1.5;
			player->y -= player->dy / 1.5;	
		}
		else
		{
			player->x -= player->dx;
			player->y -= player->dy;
		}
	}
	if (window->keys.a)
	{
		player->y -= player->dx;
		player->x += player->dy;
	}
	if (window->keys.d)
	{
		player->y += player->dx;
		player->x -= player->dy;
	}
	draw_player(window);
	return (0);
}

int	key_press(int keycode, t_window *window)
{
	t_player_pos	*player;

	player = get_player_instance();
	if (keycode == 65307)
		return (destroy_window(window));
	if (!window->keys.w && keycode == 'w') {
		ft_printf("setting w to true\n");
		window->keys.w = true;
	}
	if (!window->keys.a && keycode == 'a') {
		ft_printf("setting a to true\n");
		window->keys.a = true;
	}
	if (!window->keys.s && keycode == 's') {
		ft_printf("setting s to true\n");
		window->keys.s = true;
	}
	if (!window->keys.d && keycode == 'd') {
		ft_printf("setting d to true\n");
		window->keys.d = true;
	}
	if (!window->keys.left && keycode == 65361) {
		ft_printf("setting left to true\n");
		window->keys.left = true;
	}
	if (!window->keys.right && keycode == 65363) {
		ft_printf("setting right to true\n");
		window->keys.right = true;
	}
	return (0);
}

int	handle_no_event(void *window)
{
	(void)(window);
	return (0);
}

int	mlx_init_stuff(t_window *window)
{
	window->bits = 4;
	window->size_line_img = WIDTH;
	window->mlx_ptr = mlx_init();
	if (window->mlx_ptr == NULL)
		return (0);
	window->win_ptr = mlx_new_window(window->mlx_ptr, WIDTH, HEIGHT, "cub");
	if (window->win_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_ptr = mlx_new_image(window->mlx_ptr, WIDTH, HEIGHT);
	if (window->img_ptr == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_window
			(window->mlx_ptr, window->win_ptr), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	window->img_data = (mlx_get_data_addr(window->img_ptr, &(window->bits),
				&(window->size_line_img), &(window->endian)));
	if (window->img_data == NULL)
		return (perror("Une erreur s'est produite "), mlx_destroy_image
			(window->mlx_ptr, window->img_ptr), mlx_destroy_window
			(window->mlx_ptr, window->win_ptr), mlx_destroy_display
			(window->mlx_ptr), free(window->mlx_ptr), 0);
	return (1);
}

static void find_player_dir(t_player_pos *player, char dir)
{
	if (dir == 'N')
		player->a = PI3;
	else if (dir == 'E')
		player->a = 0;
	else if (dir == 'S')
		player->a = PI2;
	else if (dir == 'W')
		player->a = PI;
}

static void	find_player(t_map *map, t_player_pos *player, char **char_map)
{
	int x;
	int y;
	
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (char_map[y][x] == 'N' || char_map[y][x] == 'E' || char_map[y][x] == 'W' || char_map[y][x] == 'S')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				find_player_dir(player, char_map[y][x]);
				return ;
			}
			x ++;
		}
		y ++;
	}
}

int	create_window(t_window *window)
{
	t_player_pos	*player;
	t_map			*mapp;

	mapp = get_map_instance();
	mapp->map = simple_tab_int(window->data.ptr.map, window);
	if (!mlx_init_stuff(window))
		return (0);
	mapp->x = window->data.ptr.width;
	mapp->y = window->data.ptr.height;
	player = get_player_instance();
	find_player(mapp, player, window->data.ptr.map);
	player->dx = cos(player->a) * 0.08;
	player->dy = sin(player->a) * 0.08;
	return (1);
}

int	destroy_window(t_window *window)
{
	all_end = clock();
	free_mlx_infos();
	(void)window;
	printf("avg time by frame = %f, %d total frames rendered, average of %f fps\n", prout / compteur, compteur, compteur / ((double)(all_end - all_start) / CLOCKS_PER_SEC));
	exit(EXIT_SUCCESS);
}