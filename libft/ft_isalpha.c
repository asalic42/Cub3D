/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:14:17 by zbp15             #+#    #+#             */
/*   Updated: 2022/11/22 17:49:00 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int argument)
{
	if ((argument >= 65 && argument <= 90)
		|| (argument >= 97 && argument <= 122))
		return (1);
	return (0);
}

/*
int main()
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

	printf("%d,%s", ft_isalpha(a), "0\n");
	printf("%d,%s", ft_isalpha(b), "0\n");
	printf("%d,%s", ft_isalpha(c), "1\n");
	printf("%d,%s", ft_isalpha(d), "0\n");
	printf("%d,%s", ft_isalpha(e), "0\n");
	printf("%d,%s", ft_isalpha(f), "1");
	return 0;
} */
