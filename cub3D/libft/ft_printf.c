/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:26 by rciaze            #+#    #+#             */
/*   Updated: 2022/12/02 11:37:56 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	what_to_print(va_list list, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
	if (c == 'd' || c == 'i')
		return (how_many_digits(va_arg(list, int)));
	if (c == 'p')
		return (ft_print_adress(va_arg(list, void *), "0123456789abcdef", 0));
	if (c == 'u')
		return (how_many_digits2(va_arg(list, unsigned int)));
	if (c == 'x')
		return (ft_print_hexa(va_arg(list, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_print_hexa(va_arg(list, unsigned int), "0123456789ABCDEF"));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += what_to_print(list, str[i]);
		}
		else
		{
			ft_putchar(str[i]);
			len++;
		}
		i++;
	}
	va_end(list);
	return (len);
}	

/* int	main(void)
{

	unsigned int i = 123245696;

	printf("%u", i);
	ft_printf("%u", i);
}
 */