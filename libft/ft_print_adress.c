/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:00:21 by rciaze            #+#    #+#             */
/*   Updated: 2022/12/02 11:37:48 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	what_size_malloc(void *p)
{
	int				count;
	long long int	n;

	n = (long long int)p;
	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n)
	{
		count++;
		n /= 16;
	}
	return (count);
}

int	ft_print_adress(void *p, char *base, int i)
{
	char						*str;
	long long unsigned int		cpy;

	if (!p)
		return (ft_putstr("(nil)"));
	if ((long long int)p == -1)
		return (ft_putstr("0xffffffffffffffff"));
	str = malloc ((what_size_malloc(p) + 1) * sizeof(char));
	if (!str)
		return (0);
	if ((long long int)p < 0)
		cpy = -(long long int)p;
	else
		cpy = (long long unsigned int)p;
	i = what_size_malloc(p);
	while (i-- > 0)
	{
		str[i] = base[cpy % 16];
		cpy /= 16;
	}
	str[what_size_malloc(p)] = '\0';
	ft_putstr("0x");
	ft_putstr(str);
	free(str);
	return (what_size_malloc(p) + 2);
}
