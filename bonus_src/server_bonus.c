/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:44:19 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/29 21:03:09 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static void	show_pid(void);
static void	receive_message(void);
static void	handle_sigusr(int signal_number, siginfo_t *info, void *context);
static void	build_message(int signal_number, pid_t client_pid,
				t_message *message);

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
	t_message			message;

	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_sigusr;
	sigemptyset(&signal_action.sa_mask);
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	ft_bzero(&message, sizeof(message));
	message.bit = -1;
	while (1)
	{
		pause();
		build_message(0, 0, &message);
		if (message.is_complete)
		{
			write(STDOUT_FILENO, message.content, message.idx);
			write(STDOUT_FILENO, "\n", 1);
			ft_bzero(&message, sizeof(message));
			message.bit = -1;
		}
	}
}

static void	handle_sigusr(int signal_number, siginfo_t *info, void *context)
{
	(void) context;
	build_message(signal_number, info->si_pid, NULL);
}

static void	build_message(int signal_number, pid_t client_pid,
				t_message *message)
{
	static int		l_signal_number;
	static pid_t	l_client_pid;

	if (!message)
	{
		l_signal_number = signal_number;
		l_client_pid = client_pid;
		return ;
	}
	message->bit++;
	if (l_signal_number == SIGUSR2)
		message->content[message->idx] |= 128 >> message->bit;
	if (message->idx == MESSAGE_SIZE - 1
		|| (message->bit == 7 && !message->content[message->idx]))
		message->is_complete = 1;
	else if (message->bit == 7)
	{
		message->bit = -1;
		message->idx++;
	}
	if (message->is_complete)
		kill(l_client_pid, SIGUSR2);
	else
		kill(l_client_pid, SIGUSR1);
}
