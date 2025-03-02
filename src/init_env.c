/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:04:05 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/01 16:20:37 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TROUVER LE DERNIER ELEMENT DE L'ENV
t_env	*lstlast_env(t_env *lst)
{
	int		i;
	t_env	*copy;

	i = 0;
	copy = lst;
	while (copy && lst->next != copy)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

//JE CREE UNE NOUVELLE STRUCT PAR ENV
t_env	*new_env(char *todup)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	while (todup[i] != '=')
		i++;
	lst->name = malloc(sizeof(char) * (i + 1));
	if (!lst->name)
		return (free (lst), NULL);
	i = 0;
	while (todup[i] != '=')
	{
		lst->name[i] = todup[i];
		i++;
	}
	lst->name[i] = '\0';
	lst->var = ft_strdup(todup);
	if (!lst->var)
		return (free(lst->name), free(lst), NULL);
	lst->next = NULL;
	return (lst);
}

//char ** pour execve
t_boolean	create_env_tab(t_core *core, char **todup)
{
	int	i;

	i = 0;
	while (todup[i])
		i++;
	core->env_dup = malloc(sizeof(char *) * (i + 1));
	if (!core->env_dup)
		return (false);
	i = 0;
	while (todup[i])
	{
		core->env_dup[i] = ft_strdup(todup[i]);
		if (!core->env_dup[i])
			return (emergency_free_tab(core->env_dup, i), false);
		i++;
	}
	core->env_dup[i] = NULL;
	return (true);
}

//Je duplique l'env dans une liste chainee et dans un char ** (pour execve)
t_boolean	duplicate_env(t_core *core, char **todup)
{
	int		i;
	t_env	*new;

	if (!create_env_tab(core, todup))
		return (false);
	i = 1;
	core->env = new_env(todup[0]);
	if (!core->env)
		return (free_tab(core->env_dup), false);
	new = core->env;
	while (todup[i])
	{
		new->next = new_env(todup[i]);
		if (!new->next)
		{
			free_tab(core->env_dup);
			emergency_free_env_var(core->env);
			return (false);
		}
		new = new->next;
		i++;
	}
	new->next = core->env;
	return (true);
}

t_boolean	create_empty_env(t_core *core)
{
	t_env	*new;

	core->env_dup = malloc(sizeof(char *));
	core->env_dup[0] = NULL;
	core->env = new_env("PWD=");
	if (!core->env)
		return (free(core->env_dup), emergency_free_env_var(core->env), false);
	new = core->env;
	new->next = new_env("OLDPWD=");
	if (!new->next)
		return (free(core->env_dup), emergency_free_env_var(core->env), false);
	new = new->next;
	new->next = new_env("HOME=");
	if (!new->next)
		return (free(core->env_dup), emergency_free_env_var(core->env), false);
	new = new->next;
	new->next = new_env("PATH=");
	if (!new->next)
		return (free(core->env_dup), emergency_free_env_var(core->env), false);
	new = new->next;
	new->next = core->env;
	return (true);
}
