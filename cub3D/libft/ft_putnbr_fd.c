/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:23:27 by rciaze            #+#    #+#             */
/*   Updated: 2022/11/25 18:55:45 by rciaze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	i;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		i = n % 10 + 48;
		if (n / 10 > 0)
			ft_putnbr_fd(n / 10, fd);
		write(fd, &i, 1);
	}
}

/* int	main(void)
{
	ft_putnbr_fd(0, 1);
	printf("\n");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");
	ft_putnbr_fd(214783647, 1);
	printf("\n");
	ft_putnbr_fd(-100, 1);
	printf("\n");
	ft_putnbr_fd(123, 1);
	printf("\n");
	ft_putnbr_fd(123456, 1);
	printf("\n");
	ft_putnbr_fd(-123456, 1);
	printf("\n");
	ft_putnbr_fd(2, 1);

} */