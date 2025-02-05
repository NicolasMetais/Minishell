/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:04:05 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/05 03:29:01 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstlast_env(t_env *lst)
{
	int	i;

	i = 0;
	while (lst && lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back_env(t_env **lst, t_env *new)
{
	if (*lst)
		lstlast_env(*lst)->next = new;
	else
		*lst = new;
}

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
	i = 0;
	while (todup[i] != '=')
	{
		lst->name[i] = todup[i];
		i++;
	}
	lst->env = ft_strdup(todup);
	lst->next = NULL;
	return (lst);
}

void	duplicate_env(t_core *core, char **todup)
{
	int		i;
	t_env	*new;

	i = 0;
	while (todup[i])
		i++;
	core->env_dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (todup[i])
	{
		core->env_dup[i] = ft_strdup(todup[i]);
		i++;
	}
	core->env_dup[i] = NULL;
	i = 1;
	core->env = new_env(todup[0]);
	new = core->env;
	while (todup[i])
	{
		new->next = new_env(todup[i]);
		new = new->next;
		i++;
	}
	new->next = core->env;
}
