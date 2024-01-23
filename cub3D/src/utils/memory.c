/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:14:36 by asalic            #+#    #+#             */
/*   Updated: 2024/01/23 18:31:34 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

t_garbage	*get_garbage(void)
{
	static t_garbage	instance;

	return (&instance);
}

void	malloc_failure(void)
{
	perror("Critical error: (malloc probably failed): ");
	exit (EXIT_FAILURE);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		malloc_failure();
	garbage_add(ptr);
	return (ptr);
}
