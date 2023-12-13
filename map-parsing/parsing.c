/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:03:04 by asalic            #+#    #+#             */
/*   Updated: 2023/12/13 20:59:44 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

/* A voir demain pour creer une liste qui contient map */

// t_listmap	*create_arg(char *str, int token)
// {
// 	t_listmap	*new_arg;

// 	new_arg = ft_calloc(1, sizeof(t_listmap));
// 	if (!new_arg)
// 		return (NULL);
// 	new_arg->value = ;
// 	new_arg->x = ;
//     new_arg->y = ;
// 	new_arg->next = NULL;
// 	return (new_arg);
// }

// void	add_arg(t_listmap **list, char *str, int token)
// {
// 	t_listmap	*new_arg;
// 	t_listmap	*current;

// 	new_arg = create_arg(str, token);
// 	if (!new_arg)
// 		return ;
// 	if (*list == NULL)
// 		*list = copy_list(new_arg);
// 	else
// 	{
// 		current = *list;
// 		while (current->next != NULL)
// 			current = current->next;
// 		current->next = copy_list(new_arg);
// 	}
// 	free(new_arg);
// }

int     is_good_map(t_listmap *list, char *map)
{
    (void)*list;
    int fd = open(map, O_RDONLY);
    char *buff;
    buff = get_next_line(fd);
    while (buff)
    {
        // list = bu
    }
    return (0);
}
