/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:44:19 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/29 21:57:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

static void	check_args(int argc);
static void	send_message(pid_t server_pid, unsigned char *message);
static void	handle_sigusr(int signal_number);
static void	send_signal_and_wait_confirmation(pid_t server_pid,
					unsigned char c, int bit);

int	main(int argc, char **argv)
{
	check_args(argc);
	send_message(ft_atoi(argv[1]), (unsigned char *) argv[2]);
	exit(EXIT_SUCCESS);
}

static void	check_args(int argc)
{
	if (argc == 3)
		return ;
	else
	{
		ft_printf("Error :\n");
		ft_printf("\tClient must be executed with 2 arguments.\n");
		ft_printf("\tExample : ./client 1 'Hellow world!'\n");
		ft_printf("\tIn this case, `1` is the server process id");
		ft_printf(" and `Hello world!` is the message to be sent.\n");
	}
	exit(EXIT_FAILURE);
}

static void	send_message(pid_t server_pid, unsigned char *message)
{
	int	bit;

	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	bit = 8;
	while (*message)
	{
		bit--;
		send_signal_and_wait_confirmation(server_pid, *message, bit);
		if (!bit)
		{
			bit = 8;
			message++;
		}
	}
	while (1)
		send_signal_and_wait_confirmation(server_pid, '\0', 0);
}

static void	handle_sigusr(int signal_number)
{
	if (signal_number == SIGUSR2)
	{
		ft_printf("Message received!\n");
		exit(EXIT_SUCCESS);
	}
}

static void	send_signal_and_wait_confirmation(pid_t server_pid,
					unsigned char c, int bit)
{
	int	signal_number;

	if (c & (1 << bit))
		signal_number = SIGUSR2;
	else
		signal_number = SIGUSR1;
	kill(server_pid, signal_number);
	usleep(MICROSECONDS);
	pause();
}
