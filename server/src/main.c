#include "server.h"

void	show_pid(void);
void	receive_signal(int signal_number, pid_t client_pid);
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

void	receive_signal(int signal_number, pid_t client_pid)
{
	(void) client_pid;
}

void	handle_sigusr(int signal_number, siginfo_t *info, void *context)
{
	(void) context;
	receive_signal(signal_number, info->si_pid);
}

void	receive_message(void)
{
	struct sigaction	signal_action;

	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_sigusr;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
	while (1)
		;
}
