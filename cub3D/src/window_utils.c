/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:30:50 by rciaze            #+#    #+#             */
/*   Updated: 2024/01/23 15:09:56 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
	window->keys.a = false;
	window->keys.s = false;
	window->keys.w = false;
	window->keys.d = false;
	window->keys.left = false;
	window->keys.right = false;
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
