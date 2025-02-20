/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:54:12 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/20 22:52:13 by nmetais          ###   ########.fr       */
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

//JE TRIE LES NOM DES ENVS DANS L'ORDRE ALPHA ET JE LES PRINT
t_boolean	print_env_alpha(t_core *core)
{
	char	**names;
	int		size;
	int		i;

	i = -1;
	size = get_env_size(core->env);
	names = malloc(sizeof(char *) * (size + 1));
	if (!names)
		return (false);
	while (++i < size)
	{
		names[i] = ft_strdup(core->env->name);
		if (!names[i])
			return (free_tab(names), false);
		core->env = core->env->next;
	}
	names[i] = NULL;
	names = sort_tab(names);
	i = 0;
	while (names[i])
	{
		rotate_env(core, names[i++]);
		printf("%s\n", core->env->var);
	}
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

t_boolean	export_parse(char *cmd, t_core *core)
{
	if (cmd[0] == '_' || ft_isalpha(cmd[0]))
		marked_or_env(cmd, core);
	else
	{
		if (!not_valid_id(cmd, "export: "))
			return (false);
	}
	return (true);
}

//EXPORT DOIT CREER DE NOUVELLES VAR D'ENV 
//ET DES VARIABLE MARQUEE SI ON PRECISE PAS DE =
//SI PAS D'ARG CA PRINT TOUT LES VAR D'ENV TRIEE ALPHABETIQUEMENT
//EXPORT TOUT SEUL DOIT AFFICHER ENV + MARKED
//EXPORT A=1 + A=$A$A EXPLOSION DE L'ENV
//EXPORT -- ou -qqch : erreur invalid option
t_boolean	export(t_core *core, t_builtin *builtin)
{
	int			i;

	i = 0;
	if (isempty(builtin->cmd) || builtin->arg_number == 1)
	{
		if (!print_env_alpha(core))
			return (false);
		else
			return (true);
	}
	if (builtin->arg_number > 1)
	{
		while (builtin->cmd[++i])
			export_parse(builtin->cmd[i], core);
	}
	return (true);
}
