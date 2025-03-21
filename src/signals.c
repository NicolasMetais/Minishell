/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:16:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/20 00:26:54 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_here_doc(int sig, siginfo_t *info, void *test)
{
	(void)test;
	(void)info;
	if (g_signal == 1 && sig == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
}

void	sigint_fork(int sig, siginfo_t *info, void *test)
{
	(void)test;
	(void)info;
	if (g_signal == 1 && sig == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
}

void	signal_here_doc(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &sigint_here_doc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	signal_fork(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &sigint_fork;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
}
