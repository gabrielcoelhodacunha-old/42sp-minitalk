#include "server.h"

void	show_pid(void);
void	handle_sigusr(int signal_number, siginfo_t *info, void *context);
void	configure_signal_action(void);

int	main(void)
{
	show_pid();
	configure_signal_action();
	while (1)
		;
	exit(EXIT_SUCCESS);
}

void	show_pid(void)
{
	ft_printf("PID : %i\n", getpid());
}

void	configure_signal_action(void)
{
	struct sigaction	signal_action;

	signal_action.sa_flags = SA_SIGINFO;
	signal_action.sa_sigaction = handle_sigusr;
	sigaction(SIGUSR1, &signal_action, NULL);
	sigaction(SIGUSR2, &signal_action, NULL);
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

void	receive_message(int signal_number, siginfo_t *info)
{
	(void) info;
	ft_printf("%i", signal_number == SIGUSR2);
}

void	handle_sigusr(int signal_number, siginfo_t *info, void *context)
{
	(void) context;
	receive_message(signal_number, info);
}
