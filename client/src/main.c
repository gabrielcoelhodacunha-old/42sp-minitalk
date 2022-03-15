#include "client.h"

static void	check_args(int argc, char **argv);
static void	send_message(pid_t server_pid, char *message);

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	check_args(argc, argv);
	server_pid = ft_atoi(argv[1]);
	send_message(server_pid, argv[2]);
	exit(EXIT_SUCCESS);
}

static void	check_args(int argc, char **argv)
{
	char	*message;

	(void) argv;
	if (argc == 3)
		return ;
	if (argc < 3)
		message = "Client requires 2 arguments.";
	else
		message = "Client requires only 2 arguments.";
	ft_printf("Error :\n\t%s\n", message);
	exit(EXIT_FAILURE);
}

void	signal_handler(int signal_number)
{
	ft_printf("%i", signal_number == SIGUSR1);
}

struct sigaction	*create_signal_action(void)
{
	struct sigaction	*signal_action;

	signal_action = malloc(sizeof(*signal_action));
	if (!signal_action)
		exit(EXIT_FAILURE);
	signal_action->sa_flags = 0 | SA_NODEFER | SA_RESTART;
	signal_action->sa_handler = signal_handler;
	return (signal_action);
}

static void	send_message(pid_t server_pid, char *message)
{
	char	idx;
	int	signal_number;
	struct sigaction	*signal_action;

	signal_action = create_signal_action();
	sigaction(SIGUSR1, signal_action, NULL);
	sigaction(SIGUSR2, signal_action, NULL);
	while (*message)
	{
		ft_printf("%c : ", *message);
		idx = 8;
		while (--idx >= 0)
		{
			if (*message & (1 << idx))
				signal_number = SIGUSR2;
			else
				signal_number = SIGUSR1;
			kill(server_pid, signal_number);
			pause();
		}
		ft_printf("\n");
		message++;
	}
	free(signal_action);
}
