/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:20:43 by albbermu          #+#    #+#             */
/*   Updated: 2024/06/19 16:22:33 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal, siginfo_t *siginfo, void *context)
{
	static int				bit_position = 7;
	static unsigned char	current_char = 0;

	(void)context;
	if (signal == SIGUSR1)
		current_char |= (1 << bit_position);
	bit_position--;
	if (bit_position < 0)
	{
		ft_putchar_fd(current_char, 1);
		bit_position = 7;
		current_char = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			handle_errors("Failed to send SIGUSR2 to client");
	}
	else if (kill(siginfo->si_pid, SIGUSR1) == -1)
		handle_errors("Failed to send SIGUSR1 to client");
}

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		handle_errors("Failed to set up SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		handle_errors("Failed to set up SIGUSR2 handler");
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("\033[35mWelcome to Minitalk\033[0m\n");
	ft_printf("Server PID: %d\n", server_pid);
	ft_printf("\033[90m[SERVER] - Waiting for messages...\033[0m\n");
	setup_signal_handling();
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
