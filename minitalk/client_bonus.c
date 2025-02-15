/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmnasfa <hmnasfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:39:33 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/02/15 18:54:15 by hmnasfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	acknowledge_signal(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("Dooooone", 1);
}

void	send_signal(pid_t pid, char c)
{
	int bit;
	
	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putstr_fd("Error: Failed to send signal. Invalid PID or process does not complete.\n", 1);
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putstr_fd("Error: Failed to send signal. Invalid PID or process does not complete.\n", 1);
				exit(1);
			}
		}
		usleep(200);
		usleep(200);
		bit++;
	}
	
}
 
int main(int ac, char **av)
{
	pid_t pid;
	int i;

	if (ac != 3)
	{
		ft_putstr_fd("Usage :  ./client <PID> <MESSAGE TO SEND> !!\n", 1);
		return (1);
	}
	
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, acknowledge_signal);
	i = 0;
	while (av[2][i])
	{
		send_signal(pid, av[2][i]);
		i++;
	}
	send_signal(pid, '\0');
	return (0);
}