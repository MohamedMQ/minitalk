/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:21:02 by mmaqbour          #+#    #+#             */
/*   Updated: 2023/02/13 13:39:01 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_received(int sig, siginfo_t *info, void *ptr)
{
	(void)ptr;
	if (sig == SIGUSR1)
	{
		write(1, "SERVER [", 8);
		ft_putnbr_fd(info->si_pid, 1);
		write(1, "] : RECEIVED YOUR TEXT. YOU CAN SEND ANY TIME", 45);
	}
	exit (1);
}

void	send_data(char c, int pid)
{
	int	i;
	int	j;

	i = 128;
	j = 0;
	(void)pid;
	while (i > 0)
	{
		if ((c & i) == i)
			j = kill(pid, SIGUSR1);
		else
			j = kill(pid, SIGUSR2);
		i = i / 2;
		usleep(300);
	}
	ft_error("", j);
}

int	main(int ac, char **av)
{
	int					a;
	int					i;
	struct sigaction	client_b;

	client_b.sa_flags = SA_SIGINFO;
	client_b.sa_sigaction = ft_received;
	i = 0;
	if (ac == 3)
	{
		sigaction(SIGUSR1, &client_b, 0);
		a = ft_atoi(av[1]);
		while (av[2][i])
			send_data(av[2][i++], a);
		send_data('\0', a);
		while (1)
			pause();
	}
	else
		write(1, "Error : Format ./client <server_pid> <message>\n", 48);
	return (0);
}
