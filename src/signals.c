/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:16:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/09 23:03:42 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//GESTION DU SIGINT (Ctrl + c)
void	handle_sigint(int sig)
{
	g_signal = sig;
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (isatty(STDIN_FILENO))
			rl_redisplay();
	}
}

void	signal_update(void)
{
	struct sigaction	sign_int;
	struct sigaction	sign_quit;
	struct sigaction	sign_z;

	sign_int.sa_handler = handle_sigint;
	sigemptyset(&sign_int.sa_mask);
	sign_int.sa_flags = 0;
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
	struct sigaction	sign_def;

	sign_def.sa_handler = SIG_DFL;
	sigemptyset(&sign_def.sa_mask);
	sign_def.sa_flags = 0;
	sigaction(SIGINT, &sign_def, NULL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
