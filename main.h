/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:02:25 by asalic            #+#    #+#             */
/*   Updated: 2024/01/16 18:18:13 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include <SDL2/SDL.h>

# define WIDTH 1020
# define HEIGHT 400

typedef struct s_data
{
    void    *ptr;
    void    *image;
    void    *window;
}t_data;

#endif