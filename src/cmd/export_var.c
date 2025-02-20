/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:38:14 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/20 22:51:38 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//DELETE_BIS
void	delete(t_core *core)
{
	t_env	*last;
	t_env	*next;

	last = lstlast_env(core->mark);
	if (get_env_size(core->mark) == 1)
	{
		free(core->mark->name);
		free(core->mark);
		core->mark = NULL;
		return ;
	}
	next = core->mark->next;
	free(core->mark->name);
	free(core->mark);
	core->mark = next;
	last->next = next;
	return ;
}

//JE RAJOUTE LA VAR D'ENV
t_boolean	add_env(t_core *core, char *var)
{
	t_env	*last;
	t_env	*new;

	new = new_env(var);
	if (!new)
		return (false);
	if (!core->env)
		core->env = new;
	else
	{
		last = lstlast_env(core->env);
		if (!last)
			return (false);
		new->next = core->env;
		last->next = new;
		core->env = new;
	}
	return (true);
}

t_boolean	re_write_var(t_core *core, char *var, char *var_name)
{
	char	*new_var;
	int		i;
	int		j;

	i = -1;
	new_var = malloc(sizeof(char) * ((ft_strlen(core->env->var)
					+ (ft_strlen(var) - (ft_strlen(var_name) + 2)) + 1)));
	while (core->env->var[++i])
	{
		if (core->env->var[i] == '=')
			j = i + 2;
		new_var[i] = core->env->var[i];
	}
	while (var[j])
	{
		new_var[i] = var[j];
		i++;
		j++;
	}
	new_var[i] = '\0';
	free(core->env->var);
	core->env->var = new_var;
	update_env_dup(core);
	return (true);
}

t_boolean	update_var(t_core *core, char *var, char *var_name
		, t_boolean append)
{

	if (env_exist(core, var_name))
	{
		rotate_env(core, var_name);
		if (append)
		{
			if (!re_write_var(core, var, var_name))
				return (false);
		}
		else
		{
			free(core->env->var);
			core->env->var = ft_strdup(var);
		}
	}
	else
	{
		if (!add_env(core, var))
			return (free(var_name), false);
	}
	return (true);
}

//JE DELETE LA MARK SI ELLE EXISTE
//SI LA VAR D'ENV EXISTE DEJA JE L'UPDATE
//SINON JE LA CREER
t_boolean	add_var(char *var, t_core *core, t_boolean append)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] != '=')
		i++;
	if (append)
		var_name = ft_substr(var, 0, i - 1);
	else
		var_name = ft_substr(var, 0, i);
	if (!var_name)
		return (false);
	del_marked(var_name, core);
	update_var(core, var, var_name, append);
	update_env_dup(core);
	free(var_name);
	return (true);
}
