/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_p_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:26:42 by raphael           #+#    #+#             */
/*   Updated: 2024/01/10 18:53:45 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_textures_path	*get_textures_instance(void)
{
	static t_textures_path	instance;
/* 
	if (instance.is_init != 1)
	{
		instance.xpm1 = NULL;
		instance.xpm2 = NULL;
		instance.xpm3 = NULL;
		instance.xpm4 = NULL;
		instance.xpm_data1 = NULL;
		instance.xpm_data2 = NULL;
		instance.xpm_data3 = NULL;
		instance.xpm_data4 = NULL;
		instance.xpm_height1 = 0;
		instance.xpm_height2 = 0;
		instance.xpm_height3 = 0;
		instance.xpm_height4 = 0;
		instance.xpm_width1 = 0;
		instance.xpm_width2 = 0;
		instance.xpm_width3 = 0;
		instance.xpm_width4 = 0;
		instance.is_init = 1;
	} */
	return (&instance);
}