/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:22:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/06 02:46:33 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_display(t_core *core, t_builtin *builtin)
{
	(void)core;
	(void)builtin;
	printf("%u\n", g_dollar_qmark);
	g_dollar_qmark = 0;
}
