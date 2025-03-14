/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:16:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/14 18:44:42 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//GESTION DU SIGINT (Ctrl + c)

void	handle_sigint(int sig, siginfo_t *info, void *test)
{
	(void)test;
	write(1, "\n", 1);
	if (g_signal == 0 && sig == SIGINT && getpid() == info->si_pid)
	{
		printf("SIPID %d\n PID %d\n", info->si_pid, getpid());
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void setup_signal(void)
{
	struct sigaction sa;
    
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    
	sa.sa_sigaction = &handle_sigint;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL); 
}

void	signal_update(void)
{
	struct sigaction	sign_int;
	struct sigaction	sign_quit;
	struct sigaction	sign_z;

	sign_int.sa_sigaction = &handle_sigint;
	sigemptyset(&sign_int.sa_mask);
	sign_int.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sign_int, NULL);
	sign_quit.sa_handler = SIG_IGN;
	sigemptyset(&sign_quit.sa_mask);
	sign_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sign_quit, NULL);
	sign_z.sa_handler = SIG_IGN;
	sigemptyset(&sign_z.sa_mask);
	sign_z.sa_flags = 0;
	sigaction(SIGTSTP, &sign_z, NULL);
}

void	signal_reset(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
