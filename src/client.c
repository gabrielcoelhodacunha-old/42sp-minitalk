#include "client.h"

void	check_args(int argc, char **argv);
void	handle_sigusr(int signal_number);
void	send_message(pid_t server_pid, char *message);

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;

	check_args(argc, argv);
	server_pid = ft_atoi(argv[1]);
	message = ft_strdup(argv[2]);
	send_message(server_pid, message);
	exit(EXIT_SUCCESS);
}

void	check_args(int argc, char **argv)
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

void	handle_sigusr(int signal_number)
{
	(void) signal_number;
}

void	send_message(pid_t server_pid, char *message)
{
	struct sigaction	signal_action;

	(void) server_pid;
	if (!message)
		exit(EXIT_FAILURE);
	signal_action.sa_flags = 0;
	signal_action.sa_handler = handle_sigusr;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
}
