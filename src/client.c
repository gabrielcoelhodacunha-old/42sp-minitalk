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
	free(message);
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

void	send_char(pid_t server_pid, char **message)
{
	static int	bit = 8;
	unsigned char	c;
	int	signal_number;

	c = **message;
	bit--;
	if (c & (1 << bit))
		signal_number = SIGUSR2;
	else
		signal_number = SIGUSR1;
	if (!bit)
	{
		bit = 8;
		(*message)++;
	}
	kill(server_pid, signal_number);
}

void	handle_sigusr(int signal_number)
{
	if (signal_number == SIGUSR2)
	{
		ft_printf("Message received!\n");
		exit(EXIT_SUCCESS);
	}
}

void	send_message(pid_t server_pid, char *message)
{
	if (!message)
		exit(EXIT_FAILURE);
	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	while (1)
	{
		send_char(server_pid, &message);
		pause();
	}
}
