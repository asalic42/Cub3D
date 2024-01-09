/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/01/09 16:49:44 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

//Close and free everything
int	close_wndo(t_window *window)
{
	int	i;

	i = 0;
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	ft_printf(GREEN"Window is closing\n"NC);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	free_garbage();
	exit (EXIT_FAILURE);
}

//Close in case of error
void	close_error(t_window *window, char *error)
{
	if (error != NULL)
		ft_printf(RED"%s"NC, error);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	free_garbage();
	exit (EXIT_FAILURE);
}
