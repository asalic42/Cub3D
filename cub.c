/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:33:42 by asalic            #+#    #+#             */
/*   Updated: 2023/12/21 17:47:53 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	print_error(char *str)
{
	ft_printf("%s\n", str);
	return (0);
}

void	init_data(t_data *data, char *av)
{
	data->x = 0;
	data->y = 0;
	data->ptr.width = 0;
	data->ptr.height = countmap_y(av, data);
	countmap_x(av, data);
	ft_maptab(av, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error(RED "Error : not enought args\n" NC));
	start_garbage();
	data.ptr.mlx = mlx_init();
	if (!data.ptr.mlx)
		return (close_error(&data, "Error : malloc failed\n"), 0);
	else
		handle_error(&data, av[1]);
	data.ptr.wndo = mlx_new_window(data.ptr.mlx, data.ptr.width * 32,
			data.ptr.height * 32, "cub3D");
	if (data.ptr.wndo == NULL)
		return (close_error(&data, "Error : malloc failed\n"), 0);
	close_wndo(&data);
	return (1);
}
