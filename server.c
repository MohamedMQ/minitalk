/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:22:18 by mmaqbour          #+#    #+#             */
/*   Updated: 2023/02/11 17:22:20 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *ptr)
{
	static int		i;
	static char		c;
	static pid_t	pid_client;

	(void)ptr;
	if (pid_client != info->si_pid)
	{
		pid_client = info->si_pid;
		i = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c = (c << 1) | 1;
	else if (sig == SIGUSR2)
		c = (c << 1) | 0;
	i++;
	if (i == 8)
	{
		ft_putchar_fd(c, 1);
		i = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	server;

	server.sa_flags = SA_SIGINFO;
	server.sa_sigaction = handler;
	if (ac == 1 && av[0])
	{
		sigaction(SIGUSR1, &server, 0);
		sigaction(SIGUSR2, &server, 0);
		pid = getpid();
		write(1, "Server started - pid ", 22);
		ft_putnbr_fd(pid, 1);
		write(1, ". \n", 4);
		while (1)
			pause();
	}
	else
		write(1, "Error : Format ./server\n", 24);
	return (0);
}
