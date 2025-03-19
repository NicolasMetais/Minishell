/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_deux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:31:24 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/19 21:34:31 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig, siginfo_t *info, void *test)
{
	(void)test;
	(void)info;
	if (g_signal == 0 && sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_mute(void)
{
	struct sigaction	sign_int;
	struct sigaction	sign_quit;

	sign_int.sa_handler = SIG_IGN;
	sigemptyset(&sign_int.sa_mask);
	sign_int.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sign_int, NULL);
	sign_quit.sa_handler = SIG_IGN;
	sigemptyset(&sign_quit.sa_mask);
	sign_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sign_quit, NULL);
}

void	signal_shell(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
