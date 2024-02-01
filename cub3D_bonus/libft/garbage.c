/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:48:52 by asalic            #+#    #+#             */
/*   Updated: 2024/02/01 19:01:44 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Doit etre call en debut de programme
t_garbage	*start_garbage(void)
{
	t_garbage	*garbage;

	garbage = get_garbage();
	garbage->head = NULL;
	garbage->tail = NULL;
	garbage->len_of_lst = 0;
	return (garbage);
}

t_garbage_lst	*new_elmt(void *pointer_to)
{
	t_garbage_lst	*new;

	new = malloc(sizeof(t_garbage_lst));
	if (!new)
		malloc_failure();
	if (!pointer_to)
		new->pointer = NULL;
	else
		new->pointer = pointer_to;
	new->next = NULL;
	return (new);
}

// Doit etre call quand nouvelle allocation
void	garbage_add(void *pointer)
{
	t_garbage		*garbage;
	t_garbage_lst	*new;

	garbage = get_garbage();
	new = new_elmt(pointer);
	if (garbage->head == NULL)
	{
		garbage->head = new;
		garbage->tail = new;
	}
	else
	{
		garbage->tail->next = new;
		garbage->tail = garbage->tail->next;
	}
	garbage->len_of_lst++;
}

// Doit etre call dans les secu ft_malloc
void	free_garbage(void)
{
	t_garbage				*garbage;
	t_garbage_lst			*save;
	int						i;

	i = -1;
	garbage = get_garbage();
	save = garbage->head;
	while (++i < garbage->len_of_lst)
	{
		if (save->pointer)
		{
			free(save->pointer);
			save->pointer = NULL;
		}
		garbage->head = save->next;
		free(save);
		save = garbage->head;
	}
}

// Doit etre call quand nouveau tableau 2D
void	add_d_t_garbage(void **double_array, int len)
{
	int			i;

	i = -1;
	while (++i < len)
		garbage_add((void *)double_array[i]);
	garbage_add((void *)double_array);
}
