#include "client.h"

void	check_args(int argc);
void	handle_sigusr(int signal_number);
void	send_message(pid_t server_pid, unsigned char *message);

volatile static int	g_confirmation_signal = 0;

int	main(int argc, char **argv)
{
	check_args(argc);
	send_message(ft_atoi(argv[1]), (unsigned char *) argv[2]);
	exit(EXIT_SUCCESS);
}

void	check_args(int argc)
{
	char	*message;

	if (argc == 3)
		return ;
	if (argc < 3)
		message = "Client requires 2 arguments.";
	else
		message = "Client requires only 2 arguments.";
	ft_printf("Error :\n\t%s\n", message);
	exit(EXIT_FAILURE);
}

void	send_signal(pid_t server_pid, unsigned char c, int bit)
{
	int	signal_number;

	if (c & (1 << bit))
		signal_number = SIGUSR2;
	else
		signal_number = SIGUSR1;
	kill(server_pid, signal_number);
}

void	handle_sigusr(int signal_number)
{
	g_confirmation_signal = signal_number;
}

#define	USLEEP_TIME 100

void	send_message(pid_t server_pid, unsigned char *message)
{
	int	bit;

	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	bit = 8;
	while (*message)
	{
		bit--;
		g_confirmation_signal = 0;
		while (!g_confirmation_signal)
		{
			send_signal(server_pid, *message, bit);
			usleep(USLEEP_TIME);
		}
		if (!bit)
		{
			bit = 8;
			message++;
		}
	}
	while (g_confirmation_signal != SIGUSR2)
	{
		kill(server_pid, SIGUSR1);
		usleep(USLEEP_TIME);
	}
	ft_printf("Message received!\n");
}
