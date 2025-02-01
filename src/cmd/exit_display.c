/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $?.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:22:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/01 01:07:27 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_display(t_core *core)
{
	printf("%d\n", core->dollars_qmark);
	core->dollars_qmark = 0;
}
