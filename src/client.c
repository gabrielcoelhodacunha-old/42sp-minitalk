/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:44:19 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/30 21:08:33 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	check_args(int argc);
static void	send_message(pid_t server_pid, unsigned char *message);
static void	handle_sigusr(int signal_number);
static void	send_signal(pid_t server_pid, unsigned char *message);

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
		ft_printf("\tExample : ./client 1000 'Hellow world!'\n");
		ft_printf("\tIn this case, `1000` is the server process id");
		ft_printf(" and `Hello world!` is the message to be sent.\n");
	}
	exit(EXIT_FAILURE);
}

static void	send_message(pid_t server_pid, unsigned char *message)
{
	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	send_signal(server_pid, message);
	while (1)
		pause();
}

static void	handle_sigusr(int signal_number)
{
	if (signal_number == SIGUSR2)
	{
		ft_printf("Message received!\n");
		exit(EXIT_SUCCESS);
	}
	send_signal(0, NULL);
}

static void	send_signal(pid_t server_pid, unsigned char *message)
{
	static pid_t			l_server_pid;
	static unsigned char	*l_message;
	static int				bit = 8;
	int						signal_number;

	if (server_pid && message)
	{
		l_server_pid = server_pid;
		l_message = message;
		return (send_signal(0, NULL));
	}
	bit--;
	if (*l_message & (1 << bit))
		signal_number = SIGUSR2;
	else
		signal_number = SIGUSR1;
	if (!bit)
	{
		bit = 8;
		l_message++;
	}
	kill(l_server_pid, signal_number);
}
