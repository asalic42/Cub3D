/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:57:34 by rciaze            #+#    #+#             */
/*   Updated: 2022/12/02 11:38:10 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char	i;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n == 0)
		write(1, "0", 1);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else
	{
		i = n % 10 + 48;
		if (n / 10 > 0)
			ft_putnbr(n / 10);
		write(1, &i, 1);
	}
}

int	how_many_digits(long int n)
{
	int	i;

	ft_putnbr(n);
	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}
