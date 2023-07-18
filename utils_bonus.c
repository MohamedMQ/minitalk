/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:22:23 by mmaqbour          #+#    #+#             */
/*   Updated: 2023/02/13 14:46:21 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(const char *str, int flag)
{
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
		{
			write(1, "Error : Enter correct pid !\n", 28);
			exit (1);
		}
		str++;
	}
	if (flag == -1)
	{
		write(1, "Error : try to Enter correct pid \n", 34);
		exit (1);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -n;
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	ft_putchar_fd(num % 10 + '0', fd);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	sum;

	sign = 1;
	sum = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\v')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
	}
	if (sum <= 0)
	{
		write(1, "Error : wrong pid \n", 19);
		exit (1);
	}
	ft_error(str, 0);
	return (sum * sign);
}
