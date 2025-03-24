/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:16:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/24 11:59:45 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_here_doc(int sig)
{
	(void)sig;
	g_signal = 2;
	g_code_signal = 130;
	printf("\n");
	close(0);
	return ;
}

void	signal_here_doc(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = sigint_here_doc;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	sigint_fork(int sig, siginfo_t *info, void *test)
{
	(void)test;
	(void)info;
	if (g_signal == 1 && sig == SIGINT)
	{
		g_code_signal = 130;
		write(1, "\n", 1);
		return ;
	}
	if (g_signal == 1 && sig == SIGQUIT)
	{
		printf("Quit (core dumped)");
		write(1, "\n", 1);
		return ;
	}
}

void	signal_fork(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &sigint_fork;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
