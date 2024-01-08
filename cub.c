/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:33:42 by asalic            #+#    #+#             */
/*   Updated: 2024/01/08 15:41:47 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	print_error(char *str)
{
	ft_printf("%s\n", str);
	return (0);
}

void	init_data(t_window *window, char *av)
{
	window->data.x = 0;
	window->data.y = 0;
	window->data.ptr.width = 0;
	window->data.ptr.height = countmap_y(av, window);
	countmap_x(av, window);
	ft_maptab(av, &window->data, window);
}

// int	main(int ac, char **av)
// {
// 	t_data	data;

// 	if (ac != 2)
// 		return (print_error(RED "Error : not enought args\n" NC));
// 	start_garbage();
	
// 	data.ptr.mlx = mlx_init();
// 	if (!data.ptr.mlx)
// 		return (close_error(&data, "Error : malloc failed\n"), 0);
// 	else
// 		handle_error(&data, av[1]);
// 	data.ptr.wndo = mlx_new_window(data.ptr.mlx, data.ptr.width * 64,
// 			data.ptr.height * 32, "cub3D");
// 	if (data.ptr.wndo == NULL)
// 		return (close_error(&data, "Error : malloc failed\n"), 0);
// 	close_wndo(&data);
// 	return (1);
// }
