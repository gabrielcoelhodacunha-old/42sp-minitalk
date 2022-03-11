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
	message[idx/sizeof(idx)] |= 128 >> (idx % sizeof(idx));
}

static void	signal_action(int signal_number, siginfo_t *info, void *context)
{
	static char	*message;
	static size_t	idx;
	char	*auxiliary;

	if (!message)
	{
		message = ft_strdup(" ");
		if (!message)
			exit(EXIT_FAILURE);
		idx = 0;
	}
	else
	{
		auxiliary = message;
		free(message);
		message = ft_strjoin(auxiliary, " ");
		if (!message)
		{
			free(auxiliary);
			exit(EXIT_FAILURE);
		}
		free(auxiliary);
		idx++;
	}
	message[idx] = '\0';
	if (signal_number == SIGUSR2)
		set_bit(message, idx);
	if (kill(SIGUSR1, info->si_pid))
	{
		ft_printf("%s", message);
		free(message);
		message = NULL;
	}
	(void) context;
}

struct sigaction	*create_signal_action(void)
{
	struct sigaction	*signal_action;

	signal_action = malloc(sizeof(*signal_action));
	if (!signal_action)
		return (NULL);
	signal_action->sa_sigaction = signal_action;
	signal_action->sa_flags = SA_NODEFER | SA_RESTART;
	sigemptyset(&(signal_action->sa_mask));
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
