/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:53:38 by asalic            #+#    #+#             */
/*   Updated: 2023/12/15 15:58:29 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

//Is it the good file ?
int	is_goodfile(char *cub)
{
	int	fd;

	fd = open(cub, O_RDONLY);
	if (fd <= 0)
	{
		perror("Error");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	end_filename(char *cub)
{
	int	i;

	i = 0;
	while (cub && cub[i +1] != '\0')
		i ++;
	return (i);
}

//Is it the good extension ?
int	is_goodext(char *cub)
{
	int	i;

	i = end_filename(cub);
	if (cub[i] == 'b')
		i --;
	else
		return (0);
	if (cub[i] == 'u')
		i --;
	else
		return (0);
	if (cub[i] == 'c')
		i --;
	else
		return (0);
	if (cub[i] == '.')
		return (1);
	else
		return (0);
}

//Global errors files
void	error_files(t_data *data, char *cub)
{
	if (!is_goodfile(cub))
	{
		ft_printf(RED"Error: Mauvais fichier\n"NC);
		close_error(data);
	}
	if (!is_goodext(cub))
	{
		ft_printf(RED"Error: Mauvaise extension\n"NC);
		close_error(data);
	}
}