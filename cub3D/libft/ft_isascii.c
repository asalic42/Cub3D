/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:50:49 by zbp15             #+#    #+#             */
/*   Updated: 2022/11/22 17:49:02 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int argument)
{
	if (argument >= 0 && argument <= 127)
		return (1);
	return (0);
}

/* int main()
{
	int c;
	int a;
	int b;
	int d;
	int e;
	int f;

	a = '0';
	b = 130;
	c = '#';
	d = 131;
	e = '\n';
	f = 't';

	printf("%d,%s", ft_isascii(a), "1\n");
	printf("%d,%s", ft_isascii(b), "1\n");
	printf("%d,%s", ft_isascii(c), "1\n");
	printf("%d,%s", ft_isascii(d), "1\n");
	printf("%d,%s", ft_isascii(e), "1\n");
	printf("%d,%s", ft_isascii(f), "1");
	return 0;
} */
