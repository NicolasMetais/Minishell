/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:54:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/15 23:04:43 by nmetais          ###   ########.fr       */
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

t_boolean	export(t_core *core, t_builtin *builtin)
{
	if (builtin->arg_number == 1)
		print_env_alpha(core);
	return (true);
}
