/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:53:53 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 19:49:44 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
