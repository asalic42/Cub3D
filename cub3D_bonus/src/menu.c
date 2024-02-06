/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:06:32 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 19:06:59 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	button_press(int mousepress, int x, int y, t_window *window)
{
	if (mousepress == 1 && x >= 786 && x <= 1186 && y >= 523 && y <= 576)
		start_game(window);
	else if (mousepress == 1 && x >= 915 && x <= 1031 && y >= 635 && y <= 692)
		exit_menu(window);
	return (0);
}

int	mouse_pos(t_window *window)
{
	t_mlx_stuff	*mlx;

	mlx = get_mlx_ptr();
	mlx_mouse_get_pos(window->mlx_ptr, window->win_ptr, \
	&window->win.mouse_x, &window->win.mouse_y);
	mlx_destroy_image(mlx->mlx_ptr, window->menu.img_data);
	if (window->win.mouse_x >= 786 && window->win.mouse_x <= 1186 && \
		window->win.mouse_y >= 523 && window->win.mouse_y <= 576)
		window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture"\
		"s/start_choose.xpm", &window->menu.width, &window->menu.height);
	else if (window->win.mouse_x >= 915 && window->win.mouse_x <= 1031 && \
		window->win.mouse_y >= 635 && window->win.mouse_y <= 692)
		window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture"\
			"s/exit_choose.xpm", &window->menu.width, &window->menu.height);
	else
		window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./texture"\
			"s/new_menu.xpm", &window->menu.width, &window->menu.height);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, \
		window->menu.img_data, 0, 0);
	return (1);
}

void	create_menu(t_window *window)
{
	t_mlx_stuff	*mlx;

	mlx = get_mlx_ptr();
	window->menu.img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/"\
		"new_menu.xpm", &window->menu.width, &window->menu.height);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, \
		window->menu.img_data, 0, 0);
	mlx_loop_hook(window->mlx_ptr, &mouse_pos, window);
	mlx_hook(window->win_ptr, ButtonPress, ButtonPressMask, &button_press, \
		window);
	mlx_hook(window->win_ptr, 17, ButtonPressMask, &exit_menu, window);
	mlx_hook(window->win_ptr, KeyPress, KeyPressMask, &esc_keypress, window);
	mlx_loop(window->mlx_ptr);
}
