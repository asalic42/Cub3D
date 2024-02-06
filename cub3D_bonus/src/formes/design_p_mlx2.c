/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_mlx2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:30:11 by rciaze            #+#    #+#             */
/*   Updated: 2024/02/06 18:30:24 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

t_mlx_stuff	*mlx_instance(void)
{
	static t_mlx_stuff	instance;

	return (&instance);
}
