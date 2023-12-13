/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:33:42 by asalic            #+#    #+#             */
/*   Updated: 2023/12/13 19:51:03 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
    t_parse parsing;

    if (ac != 2)
    {
        ft_printf(RED "Error : not enought args\n" NC);
        return (0);
    }
    handle_error(&parsing, av[1]);
    return (0);
}
