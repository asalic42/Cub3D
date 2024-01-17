/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:43:35 by zbp15             #+#    #+#             */
/*   Updated: 2022/11/22 17:48:14 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argument)
{
	if ((argument >= 65 && argument <= 90)
		|| (argument >= 97 && argument <= 122)
		|| (argument >= 48 && argument <= 57))
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

	printf("%d,%s", ft_isalnum(a), "1\n");
	printf("%d,%s", ft_isalnum(b), "0\n");
	printf("%d,%s", ft_isalnum(c), "1\n");
	printf("%d,%s", ft_isalnum(d), "1\n");
	printf("%d,%s", ft_isalnum(e), "0\n");
	printf("%d,%s", ft_isalnum(f), "1");
	return 0;
}
 */
