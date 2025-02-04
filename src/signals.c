/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:16:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/04 05:50:31 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{

	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(void)
{
	struct sigaction	sign;

	sign.sa_handler = handle_sigint;
	sigemptyset(&sign.sa_mask);
	sign.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sign, NULL);
}
