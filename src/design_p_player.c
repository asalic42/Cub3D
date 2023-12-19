/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:59:40 by rciaze            #+#    #+#             */
/*   Updated: 2023/12/19 18:17:40 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

t_player_pos	*get_player_instance(void)
{
	static t_player_pos	instance;

	return (&instance);
}