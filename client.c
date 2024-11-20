/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albbermu <albbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:32:50 by albbermu          #+#    #+#             */
/*   Updated: 2024/06/19 16:22:44 by albbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
		handle_errors("Usage: ./client <PID> <Message>");
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
			handle_errors("PID must be a number");
		i++;
	}
	if (*argv[2] == 0)
		handle_errors("Message cannot be empty");
}

void	send_message(pid_t server_pid, char *message)
{
	unsigned char	c;
	int				bit_count;

	while (*message)
	{
		c = *message;
		bit_count = 8;
		while (bit_count--)
		{
			if (c & 0b10000000)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(100);
			c <<= 1;
		}
		message++;
	}
}

void	signal_handler(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("\033[92mCharacter has been successfully received\033[0m\n");
}

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		handle_errors("Failed to set up SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		handle_errors("Failed to set up SIGUSR2 handler");
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	validate_arguments(argc, argv);
	server_pid = ft_atoi(argv[1]);
	setup_signal_handling();
	send_message(server_pid, argv[2]);
	send_message(server_pid, "\n");
	return (EXIT_SUCCESS);
}
