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

static void	signal_handler(int signal_number)
{
	if (signal_number == SIGUSR1)
		ft_printf("0");
	else
		ft_printf("1");
}

static void	receive_message(void)
{
	struct sigaction	signal_action;

	signal_action.sa_handler = signal_handler;
	signal_action.sa_flags = 0;
	sigemptyset(&signal_action.sa_mask);
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	while (pause())
		;
}
