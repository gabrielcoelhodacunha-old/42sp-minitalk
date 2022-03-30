/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:44:19 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/30 21:11:06 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static void	show_pid(void);
static void	receive_message(void);
static void	handle_sigusr(int signal_number, siginfo_t *info, void *context);
static void	build_message_and_send_confirmation(int signal_number,
				pid_t client_pid);

int	main(void)
{
	show_pid();
	receive_message();
	exit(EXIT_SUCCESS);
}

static void	show_pid(void)
{
	ft_printf("PID : %i\n", getpid());
}

static void	receive_message(void)
{
	struct sigaction	signal_action;

	ft_bzero(&signal_action, sizeof(signal_action));
	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_sigusr;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	build_message_and_send_confirmation(0, 0);
	while (1)
		pause();
}

static void	handle_sigusr(int signal_number, siginfo_t *info, void *context)
{
	(void) context;
	build_message_and_send_confirmation(signal_number, info->si_pid);
}

static void	build_message_and_send_confirmation(int signal_number,
				pid_t client_pid)
{
	static t_message	message;

	if (!signal_number && !client_pid)
	{
		ft_bzero(&message, sizeof(message));
		message.bit = -1;
		return ;
	}
	message.bit++;
	if (signal_number == SIGUSR2)
		message.content[message.idx] |= 128 >> message.bit;
	if (message.bit == 7 && message.content[message.idx])
	{
		message.bit = -1;
		message.idx++;
	}
	else if (message.bit == 7)
	{
		ft_printf("%s\n", message.content);
		build_message_and_send_confirmation(0, 0);
		kill(client_pid, SIGUSR2);
		return ;
	}
	kill(client_pid, SIGUSR1);
}
