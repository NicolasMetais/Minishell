/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:54:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 16:44:10 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TRIE A BULLE POUR TRIER LES NOMS
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

char	**setup_names(t_core *core, char **names, int env_size, int size)
{	
	int	i;

	i = -1;
	while (++i < env_size)
	{
		names[i] = ft_strdup(core->env->var);
		if (!names[i])
			return (free_tab(names), NULL);
		core->env = core->env->next;
	}
	while (i < size)
	{
		names[i] = ft_strdup(core->mark->name);
		if (!names[i])
			return (free_tab(names), NULL);
		core->mark = core->mark->next;
		i++;
	}
	names[i] = NULL;
	return (names);
}

//JE TRIE LES NOM DES ENVS DANS L'ORDRE ALPHA ET JE LES PRINT
t_boolean	print_env_alpha(t_core *core)
{
	char	**names;
	int		i;
	int		size;
	int		env_size;

	i = -1;
	env_size = get_env_size(core->env);
	size = env_size + get_env_size(core->mark);
	names = malloc(sizeof(char *) * (size + 1));
	if (!names)
		return (false);
	names = setup_names(core, names, env_size, size);
	if (!names)
		return (false);
	names = sort_tab(names);
	while (names[++i])
		printf("export %s\n", names[i]);
	return (free_tab(names), true);
}

//JE VERIFIE QUE EXPORT SOIT BIEN VIDE. EXEMPLE SI JE MET EXPORT $TEST.
//TEST EXISTE PAS DONC EXPORT EST VIDE MAIS J'AI 2 ARG
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

//EXPORT DOIT CREER DE NOUVELLES VAR D'ENV 
//ET DES VARIABLE MARQUEE SI ON PRECISE PAS DE =
//SI PAS D'ARG CA PRINT TOUT LES VAR D'ENV + MARQUEE TRIEE ALPHABETIQUEMENT
t_boolean	export(t_core *core, t_cmd *cmd)
{
	int			i;

	i = 0;
	if (isempty(cmd->args) || cmd->args_nb == 1)
		return (print_env_alpha(core));
	if (cmd->args[1][0] == '-')
	{
		if (invalid_option(cmd, "export: ", core))
			return (true);
		else
			return (false);
	}
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] == '_'
			|| ft_isalpha(cmd->args[i][0]))
			marked_or_env(cmd->args[i], core);
		else
		{
			if (!not_valid_id(cmd->args[i], "export: ", core))
				return (false);
		}
	}
	return (true);
}
