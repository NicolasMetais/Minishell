/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:42:01 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 09:53:11 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dynamic_delete_failed(char ***tab)
{
	(*tab)++;
	free_split_get_fd(*tab);
}

char	*dynamic_delete(char *old)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(old);
	new = malloc(sizeof(char) * len);
	if (!new)
		return (free(old), NULL);
	i = 0;
	j = 1;
	while (i < len - 1)
	{
		new[i] = old[j];
		j++;
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

char	*dynamic_copy(char *old, char c)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(old);
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (free(old), NULL);
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	if (old)
		free(old);
	return (new);
}

void	incr_empty_file(char **tmp, char **str)
{
	(*tmp) += 2;
	(*str) += 2;
}
