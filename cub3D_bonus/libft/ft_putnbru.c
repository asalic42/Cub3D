/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:27:36 by zbp15             #+#    #+#             */
/*   Updated: 2022/12/02 11:38:05 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr2(unsigned int n)
{
	char	i;

	if (n == 0)
		write(1, "0", 1);
	else
	{
		i = n % 10 + 48;
		if (n / 10 > 0)
			ft_putnbr2(n / 10);
		write(1, &i, 1);
	}
}

int	how_many_digits2(unsigned long int n)
{
	int	i;

	ft_putnbr2(n);
	i = 0;
	if (n == 0)
		i = 1;
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}
