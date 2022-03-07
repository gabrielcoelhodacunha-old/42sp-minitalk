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

static void	send_message(pid_t server_pid, char *message)
{
	ft_printf("Server PID : %i\n", server_pid);
	ft_printf("Message : %s\n", message);
	kill(server_pid, SIGUSR2);
	kill(server_pid, SIGUSR1);
	kill(server_pid, SIGUSR1);
}
