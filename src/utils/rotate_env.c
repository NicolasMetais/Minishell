/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:50:52 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/05 07:02:54 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ROTATE THE ENV VARIABLE LINKED LIST ON THE GIVEN NAME
 * IT'S "BASICALY" A SELECT_ENV WITH LINKED LIST
 * 
 * @param core 
 * @param var_name 
 * @return t_env 
 */

t_env	*rotate_env(t_core *core, char *var_name)
{
	while (ft_strncmp(core->env->name, var_name, ft_strlen(var_name)) != 0)
		core->env = core->env->next;
	return (core->env);
}
