/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:33:42 by asalic            #+#    #+#             */
/*   Updated: 2023/12/15 15:57:28 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int print_error(char *str)
{
    ft_printf("%s\n", str);
    return (1);
}



//Close in case of error
void	close_error(t_data *data)
{
	mlx_destroy_display(data->ptr.mlx);
	free(data->ptr.mlx);
	exit (EXIT_FAILURE);
}

void	init_data(t_data *data)
{
	data->x = 0;
	data->y = 0;
	data->ptr.height = 0;
	data->ptr.width = 0;
}

int main(int ac, char **av)
{
    // t_parse parsing;
    t_data  data;

    if (ac != 2)
        return (print_error(RED "Error : not enought args\n" NC));
    start_garbage();
	init_data(&data);
    data.ptr.mlx = mlx_init();
    if (!data.ptr.mlx)
        return (1);
	else if (!handle_error(&data, av[1]))
		return (1);
    countmap_x(av[1], &data);
    data.ptr.height = countmap_y(av[1], &data);
    data.ptr.map = ft_maptab(av[1], &data);
    if (!main_parse(data.ptr.map, &data))
    {
        ft_printf(RED"Error : wrong map\n"NC);
        return (1);
    }
    data.ptr.wndo = mlx_new_window(data.ptr.mlx, data.ptr.width * 32,
			data.ptr.height * 32, "cub3D");
	if (data.ptr.wndo == NULL)
	{
		free(data.ptr.mlx);
		return (0);
	}
    // close_wndow(&data);
    return (0);
}
