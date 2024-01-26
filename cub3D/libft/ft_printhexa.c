/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:34:50 by zbp15             #+#    #+#             */
/*   Updated: 2024/01/15 17:08:46 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many_digits3(unsigned int n)
{
	int				count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n /= 16;
	}
	return (count);
}

int	ft_print_hexa(unsigned int n, char *base)
{
	char	*str;
	int		i;
	int		c;

	c = how_many_digits3(n);
	str = ft_malloc ((c + 1) * sizeof(char));
	if (!str)
		return (0);
	i = c;
	while (i-- > 0)
	{
		str[i] = base[n % 16];
		n /= 16;
	}
	str[c] = '\0';
	ft_putstr(str);
	return (c);
}
