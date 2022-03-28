#include "server.h"

void	show_pid(void);
void	handle_sigusr(int signal_number, siginfo_t *info, void *context);
void	receive_message(void);

int	main(void)
{
	show_pid();
	receive_message();
	exit(EXIT_SUCCESS);
}

void	show_pid(void)
{
	ft_printf("PID : %i\n", getpid());
}

#define MESSAGE_SIZE 1000001

void	build_and_show_message(int signal_number, pid_t client_pid)
{
	static unsigned char	message[MESSAGE_SIZE];
	static int	idx = 0;
	static int	bit = -1;
	static int	l_signal_number;
	static pid_t	l_client_pid;

	if (signal_number && client_pid)
	{
		l_signal_number = signal_number;
		l_client_pid = client_pid;
		return ;
	}
	bit++;
	if (l_signal_number == SIGUSR2)
		message[idx] |= 128 >> bit;
	if (idx == MESSAGE_SIZE - 1 || (bit == 7 && !message[idx]))
	{
		write(STDOUT_FILENO, message, idx);
		write(STDOUT_FILENO, "\n", 1);
		ft_bzero(message, idx + 1);
		idx = 0;
		bit = -1;
		kill(l_client_pid, SIGUSR2);
		return ;
	}
	else if (bit == 7)
	{
		bit = -1;
		idx++;
	}
	kill(l_client_pid, SIGUSR1);
}

void	handle_sigusr(int signal_number, siginfo_t *info, void *context)
{
	(void) context;
	build_and_show_message(signal_number, info->si_pid);
}

void	receive_message(void)
{
	struct sigaction	signal_action;

	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = SA_SIGINFO | SA_NODEFER;
	signal_action.sa_sigaction = handle_sigusr;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	while (1)
	{
		pause();
		build_and_show_message(0, 0);
	}
}
