/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:33:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/07 08:11:26 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_size(t_env	*env)
{
	int		i;
	t_env	*copy;

	i = 0;
	copy = env;
	while (copy->next != env)
	{
		copy = copy->next;
		i++;
	}
	return (i);
}
