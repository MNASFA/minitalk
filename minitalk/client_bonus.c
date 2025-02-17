/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmnasfa <hmnasfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:39:33 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/02/17 13:27:17 by hmnasfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	acknowledge_signal(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("\nDooooone\n", 1);
}

void	send_signal(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(300);
		usleep(300);
		bit++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	if (ac != 3)
	{
		ft_putstr_fd("Usage :  ./client_bonus <PID> <MESSAGE TO SEND> !!\n", 1);
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid < 1 || kill(pid, 0) == -1)
	{
		ft_putstr_fd("Error: PID not exist or overflow occurred!\n", 1);
		return (1);
	}
	signal(SIGUSR1, acknowledge_signal);
	i = 0;
	while (av[2][i])
	{
		send_signal(pid, av[2][i]);
		usleep(500);
		i++;
	}
	send_signal(pid, '\0');
	return (0);
}
