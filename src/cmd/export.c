/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:54:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/16 19:46:18 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sort_tab(char **names)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (names[i])
	{	
		j = 0;
		while (names[j])
		{	
			if (ft_strcmp(names[i], names[j]) < 0)
			{
				temp = names[i];
				names[i] = names[j];
				names[j] = temp;
			}
		j++;
		}
	i++;
	}
	return (names);
}

void	print_env_alpha(t_core *core)
{
	char	**names;
	int		size;
	int		i;

	i = 0;
	size = get_env_size(core->env);
	names = malloc(sizeof(char *) * size + 1);
	while (i < size)
	{
		names[i] = ft_strdup(core->env->name);
		core->env = core->env->next;
		i++;
	}
	names = sort_tab(names);
	i = 0;
	while (names[i])
	{
		rotate_env(core, names[i++]);
		printf("%s\n", core->env->var);
	}
}

t_boolean	isempty(char **tab)
{
	int			i;
	t_boolean	empty;

	i = 1;
	empty = false;
	while (tab[i])
	{
		if (tab[i][0] == '\0')
			empty = true;
		else
			empty = false;
		i++;
	}
	return (empty);
}


t_boolean	export(t_core *core, t_builtin *builtin)
{
	int	i;

	i = 0;
	if (isempty(builtin->cmd) || builtin->arg_number == 1)
	{
		print_env_alpha(core);
		return (true);
	}
	if (builtin->arg_number > 1)
	{
		while (builtin->cmd[++i])
		{
			if (builtin->cmd[i][0] == '_' || ft_isalpha(builtin->cmd[i][0]))
				marked_or_env(builtin->cmd[i], core);
			else
				not_valid_id(builtin->cmd[i], "export0: ");
		}
	}
	return (true);
}
/* 	t_env *copy;

	copy = core->mark;
	while (copy->next != core->mark)
	{
		printf("%s\n", copy->name);
		copy = copy->next;
	} */