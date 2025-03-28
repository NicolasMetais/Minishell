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
	int		i;

	if (end && ((int)ft_strlen(old) <= c))
	{
		*end = 1;
		return (old);
	}
	else if ((int)ft_strlen(old) < c)
		return (old);
	new = malloc(sizeof(char) * (ft_strlen(old) - c + 1));
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
	if (!new_tab[0])
		return (free_split_init(new_tab, 2), free(new), NULL);
	new_tab[1] = NULL;
	free(new);
	return (new_tab);
}

char	**realloc_add_to_tab(char **tab, char *new)
{
	char	**new_tab;
	int		len;
	int		i;

	i = 0;
	len = command_counter(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (free(new), NULL);
	if (!tab)
		return (new_tab_init(new_tab, new));
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new)
			return (free_split_init(new_tab, i), free(new), NULL);
		i++;
	}
	new_tab[i] = ft_strdup(new);
	if (!new_tab[i])
		return (free_split_init(new_tab, i), free(new), NULL);
	new_tab[i + 1] = NULL;
	free(new);
	return (free_split(tab), new_tab);
}
