/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:34 by asalic            #+#    #+#             */
/*   Updated: 2024/01/11 03:15:03 by asalic           ###   ########.fr       */
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

char	*cut_until(char *str, char cut)
{
	int i;
	char *new_cut;

	i = 0;
	while (str[i] && str[i] != cut)
		i ++;
	new_cut = ft_malloc((i+1) * sizeof(char));
	i = 0;
	while (str[i] && str[i] != cut)
	{
		new_cut[i] = str[i];
		i ++;
	}
	new_cut[i] = '\0';
	return (new_cut);
}

char	*cut_from(char *str, char cut)
{
	int i;
	char *new_cut;
	int j;
	
	i = 0;
	while (str[i] && str[i] != cut)
		i ++;
	if (str[i] == cut)
		i ++;
	j = 0;
	new_cut = ft_malloc(ft_strlen(str + i) * sizeof(char));
	while (str[i] && str[i] != '\n')
		new_cut[j++] = str[i++];
	new_cut[j] = '\0';
	return (new_cut);		
}