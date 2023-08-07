/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 14:33:07 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/01 17:48:41 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_message(int signo)
{
	const char	*sigs[] = {NULL, "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", \
	"SIGTRAP", "SIGABRT", "SIGEMT", "SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV", \
	"SIGSYS", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGURG", "SIGSTOP", "SIGTSTP", \
	"SIGCONT", "SIGCHLD", "SIGTTIN", "SIGTTOU", "SIGIO", "SIGXCPU", "SIGXFSZ", \
	"SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2"};

	if (signo > 128 && signo < 156)
		ft_dprintf(2, "%s: %i\n", sigs[signo - 128], signo - 128);
}

void	sigint_reprompt(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 0);
	rl_on_new_line();
	rl_redisplay();
}

void	empty_sighandler(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', 0);
}
