#include "server.h"

static void	show_pid(void);
static void	receive_message(void);

int	main(void)
{
	show_pid();
	receive_message();
	exit(EXIT_SUCCESS);
}

static void	show_pid(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID : %i\n", pid);
}

void	set_bit(char *message, size_t idx)
{
	size_t	midx;
	size_t	shift;

	midx = sizeof(idx) * 8;
	shift = idx % midx;
	midx = idx / midx;
	message[midx] |= 128 >> shift;
}

void	signal_handler(int signal_number, siginfo_t *info, void *context)
{
/*
	static char	*message;
	static size_t	idx;
	char	*auxiliary;

	(void) context;
	if (!message)
	{
		message = ft_strdup("");
		if (!message)
			exit(EXIT_FAILURE);
	}
	if (!(idx % 8))
	{
		auxiliary = message;
		free(message);
		message = ft_strjoin(auxiliary, " ");
		free(auxiliary);
		if (!message)
			exit(EXIT_FAILURE);
		message[ft_strlen(message) - 1] = '\0';
	}
	if (signal_number == SIGUSR2)
		set_bit(message, idx);
	if (kill(SIGUSR1, info->si_pid))
	{
		ft_printf("Client PID : %i\n", info->si_pid);
		ft_printf("%s\n", message);
		free(message);
		message = NULL;
		idx = 0;
	}
	idx++;
*/
	(void) context;
	ft_printf("Client PID : %i\n", info->si_pid);
	if (signal_number == SIGUSR1)
		kill(info->si_pid, SIGUSR2);
	else
		kill(info->si_pid, SIGUSR1);
}

struct sigaction	*create_signal_action(void)
{
	struct sigaction	*signal_action;

	signal_action = malloc(sizeof(*signal_action));
	if (!signal_action)
		exit(EXIT_FAILURE);
	signal_action->sa_flags = SA_SIGINFO;
	signal_action->sa_sigaction = signal_handler;
	return (signal_action);
}

static void	receive_message(void)
{
	struct sigaction	*signal_action;

	signal_action = create_signal_action();
	sigaction(SIGUSR1, signal_action, NULL);
	sigaction(SIGUSR2, signal_action, NULL);
	while (pause())
		;
	free(signal_action);
}
