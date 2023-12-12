/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:34:50 by zbp15             #+#    #+#             */
/*   Updated: 2022/12/02 11:38:16 by rciaze           ###   ########.fr       */
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
	str = malloc ((c + 1) * sizeof(char));
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
	free(str);
	return (c);
}
