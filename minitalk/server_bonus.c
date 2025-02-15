/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmnasfa <hmnasfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:40:04 by hmnasfa           #+#    #+#             */
/*   Updated: 2025/02/15 16:22:42 by hmnasfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handle_signal(int signum, siginfo_t *info, void *context)
{
    static int bit;
    static char character;
    static pid_t last_client_pid;
    (void)context;
    
    if (last_client_pid != info->si_pid)
    {
        bit = 0;
        character = 0;
        last_client_pid = info->si_pid;
    }
    
    if (signum == SIGUSR2)
        character |= (1 << bit);
    bit++;
    
    if (bit == 8)
    {
        if (character == '\0')
        {
            write(1, "\n", 1);
            kill(info->si_pid, SIGUSR1);
        }
        else
            write(1, &character, 1);
        bit = 0;
        character = 0;
    }
}

int main(void)
{
    struct sigaction sa;
    
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    
    ft_putstr_fd ("Server PID : ",1);
    ft_putnbr_fd (getpid(), 1);
    ft_putchar_fd('\n', 1);

    sigaction (SIGUSR1, &sa, NULL);
    sigaction (SIGUSR2, &sa, NULL);
        
    while (1)
        pause();
    return 0;
}
