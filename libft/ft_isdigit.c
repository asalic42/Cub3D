/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:06 by zbp15             #+#    #+#             */
/*   Updated: 2022/11/22 17:50:33 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int argument)
{
	if (argument >= 48 && argument <= 57)
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
	b = '(';
	c = 'A';
	d = '2';
	e = '\n';
	f = 't';

	printf("%d,%s", ft_isdigit(a), "1\n");
	printf("%d,%s", ft_isdigit(b), "0\n");
	printf("%d,%s", ft_isdigit(c), "0\n");
	printf("%d,%s", ft_isdigit(d), "1\n");
	printf("%d,%s", ft_isdigit(e), "0\n");
	printf("%d,%s", ft_isdigit(f), "0");
	return 0;
} */
