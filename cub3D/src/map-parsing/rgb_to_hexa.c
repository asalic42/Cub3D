/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalic <asalic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:07:55 by asalic            #+#    #+#             */
/*   Updated: 2024/01/23 18:31:51 by asalic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"

/* Convert the rgb color into hexadecimal color
	(step 1 : rgb by rgb) */
static char	*convert_hexa(unsigned int nb, char *base)
{
	int		i;
	int		c;
	char	*str;

	c = how_many_digits3(nb);
	str = ft_malloc((c + 2) * sizeof(char));
	i = c;
	if (i == 1)
	{
		while (i >= 0)
			str[i--] = '0';
		str[c +1] = '\0';
	}
	else
	{
		while (i-- > 0)
		{
			str[i] = base[nb % 16];
			nb /= 16;
		}
		str[c] = '\0';
	}
	return (str);
}

/* Conversion of all the rgb into hexadecimal color
	(step 2: all of rgb into one chain) */
char	*convert_rgb_to_hexa(char **rgb)
{
	char	*buf;
	int		hexa;
	char	*tmp;
	int		i;

	hexa = 0;
	i = 0;
	buf = NULL;
	tmp = NULL;
	while (rgb[i])
	{
		hexa = ft_atoi(rgb[i]);
		if (buf == NULL)
			buf = convert_hexa(hexa, "0123456789ABCDEF");
		else
		{
			tmp = convert_hexa(hexa, "0123456789ABCDEF");
			buf = ft_strjoin(buf, tmp);
		}
		i ++;
	}
	return (buf);
}

/* Check if the character is a number or an alphabetic
	(used in the conversion into hexdecimal case) */
static int	hexachar_to_decimal(char hex_char)
{
	if (hex_char >= '0' && hex_char <= '9')
		return (hex_char - '0');
	else if (hex_char >= 'A' && hex_char <= 'F')
		return (hex_char - 'A' + 10);
	else
		return (-1);
}

/* Convert the hexadecimal color into a decimal
	to be used in the mlx function that demands an int */
long	hexa_to_decimal(const char *hexadecimal)
{
	long	result;
	int		digit_value;

	result = 0;
	while (*hexadecimal != '\0')
	{
		digit_value = hexachar_to_decimal(*hexadecimal);
		if (digit_value == -1)
		{
			ft_printf(RED"Error : not a character hexadecimal"NC);
			return (-1);
		}
		result = result * 16 + digit_value;
		hexadecimal++;
	}
	return (result);
}
