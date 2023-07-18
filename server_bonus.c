/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:22:13 by mmaqbour          #+#    #+#             */
/*   Updated: 2023/02/13 13:24:59 by mmaqbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	process_bits(int *bit_counter, char *received_char, pid_t *pid_client)
{
	if (*bit_counter == 8)
	{
		ft_putchar_fd(*received_char, 1);
		if (!*received_char)
		{
			kill(*pid_client, SIGUSR1);
			pid_client = 0;
			return ;
		}
		*bit_counter = 0;
		*received_char = 0;
	}
}

void	handler(int sig, siginfo_t *info, void *ptr)
{
	static int		i;
	static char		c;
	static pid_t	pid_client_bonus;

	(void)ptr;
	if (pid_client_bonus != info->si_pid)
	{
		pid_client_bonus = info->si_pid;
		i = 0;
		c = 0;
	}
	if (sig == SIGUSR1)
		c = (c << 1) | 1;
	else if (sig == SIGUSR2)
		c = (c << 1) | 0;
	i++;
	process_bits(&i, &c, &pid_client_bonus);
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	server_b;

	server_b.sa_flags = SA_SIGINFO;
	server_b.sa_sigaction = handler;
	if (ac == 1 && av[0])
	{
		sigaction(SIGUSR1, &server_b, 0);
		sigaction(SIGUSR2, &server_b, 0);
		pid = getpid();
		write(1, "Server started - pid ", 22);
		ft_putnbr_fd(pid, 1);
		write(1, ". \n", 4);
		while (1)
			pause();
	}
	else
		write(1, "Error : Format ./server_bonus\n", 30);
	return (0);
}
