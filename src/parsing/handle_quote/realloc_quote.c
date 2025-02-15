/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 13:42:39 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-12 13:42:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*realloc_line(char	*old, int c, int *end)
{
	char	*new;
	char	*tmp;
	int		i;

	if (ft_strlen(old + c) == 0)
	{
		*end = 1;
		return (old);
	}
	tmp = old;
	new = malloc(sizeof(char) * (ft_strlen(old) - c) + 1);
	if (!new)
		return (NULL);
	old += c;
	i = 0;
	while (*old)
	{
		new[i] = *old;
		old++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**new_tab_init(char **new_tab, char *new)
{
	new_tab[0] = ft_strdup(new);
	new_tab[1] = NULL;
	free(new);
	return (new_tab);
}

char	**realloc_quote(char **tab, char *new)
{
	char	**new_tab;
	int		len;
	int		i;

	i = 0;
	len = command_counter(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	if (!tab)
		return (new_tab_init(new_tab, new));
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new)
			return (NULL);
		i++;
	}
	new_tab[i] = ft_strdup(new);
	if (!new_tab[i])
		return (NULL);
	new_tab[i + 1] = NULL;
	return (free_split(tab), free(new), new_tab);
}