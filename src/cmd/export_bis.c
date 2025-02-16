/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:11:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/16 21:29:15 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	marked_exist(char *var, t_core *core)
{
	t_env	*copy;

	if (!core->mark)
		return (false);
	copy = core->mark;
	while (copy->next != core->mark)
	{
		if (ft_strcmp(var, copy->name) == 0)
			return (true);
		copy = copy->next;
	}
	return (false);
}

t_boolean	new_marked(char *var, t_core *core)
{
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
		return (false);
	new->name = ft_strdup(var);
	if (!new->name)
		return (free(new), false);
	if (!core->mark)
		core->mark = new;
	else
	{
		last = lstlast_env(core->mark);
		last->next = new;
	}
	//last->next = core->mark;
	return (true);
}

t_boolean	marked_or_env(char *var, t_core *core)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '=')
			break ;
		if (!(ft_isalnum(var[i])) && !(var[i] == '_'))
			return (not_valid_id(var, "export1: "));
	}
	if (!marked_exist(var, core))
	{
		printf("JE CREE LA VAR\n");
		if (!new_marked(var, core))
			return (false);
	}
	return (true);
}
