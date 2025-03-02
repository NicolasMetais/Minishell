/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_marked.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:11:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/02 13:55:45 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//DELETE DE LA VAR MARQUEE
void	del_marked(char *var, t_core *core)
{
	t_env	*copy;

	copy = core->mark;
	while (core->mark)
	{
		if (ft_strcmp(core->mark->name, var) == 0)
		{
			delete(core);
			break ;
		}
		core->mark = core->mark->next;
		if (core->mark == copy)
			break ;
	}
}

//SI LA VARIABLE MARQUEE EXISTE DEJA JE NE LA DUPLIQUE PAS
t_boolean	marked_exist(char *var, t_core *core)
{
	t_env	*copy;

	if (!core->mark || !var)
		return (false);
	copy = core->mark;
	while (copy)
	{
		if (copy->name && ft_strcmp(copy->name, var) == 0)
			return (true);
		copy = copy->next;
		if (copy == core->mark)
			break ;
	}
	return (false);
}

//JE CREER UN NOUVELLE VAR MARQUE AVEC JUSTE UN NOM
t_boolean	new_marked(char *var, t_core *core)
{
	t_env	*new;
	t_env	*last;

	if (env_exist(core, var))
		return (true);
	new = malloc(sizeof(t_env));
	if (!new)
		return (false);
	new->name = ft_strdup(var);
	if (!new->name)
		return (free(new), false);
	if (!core->mark)
	{
		core->mark = new;
		core->mark->next = core->mark;
	}
	else
	{
		last = lstlast_env(core->mark);
		last->next = new;
		new->next = core->mark;
	}

	return (true);
}

//JE REGARDE SI JE TROUVE UN =. 
//SI J'EN TROUVE UN JE SAIS QUE C'EST UNE VAR D'ENV
//SI J'EN TROUVE PAS JE MARQUE LA VAR ET JE LA MET DANS UNE AUTRE LISTE CHAINEE
t_boolean	marked_or_env(char *var, t_core *core)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '+' && (int)ft_strlen(var) > i)
		{
			if (var[i + 1] == '=')
				return (add_var(var, core, true));
		}
		if (var[i] == '=')
			return (add_var(var, core, false));
		if (!(ft_isalnum(var[i])) && !(var[i] == '_'))
		{
			not_valid_id(var, "export: ");
			return (false);
		}
	}
	if (!marked_exist(var, core))
	{
		if (!new_marked(var, core))
			return (false);
	}
	return (true);
}
