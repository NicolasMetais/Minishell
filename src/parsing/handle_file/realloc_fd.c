/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:17:04 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/19 21:45:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_cmd(char **cmd, int supp)
{
	int		i;
	int		j;
	char	**cmd_dup;
	int		len;

	len = command_counter(cmd);
	cmd_dup = malloc(sizeof(char *) * len);
	if (!cmd_dup)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < len - 1)
	{
		if (i == supp)
			j++;
		cmd_dup[i] = ft_strdup(cmd[j]);
		if (!cmd_dup[i])
			return (free_split_init(cmd_dup, i), free_split(cmd), NULL);
		j++;
	}
	free_split(cmd);
	cmd_dup[i] = NULL;
	return (cmd_dup);
}

char	*realloc_str_file(char *str, int i, int j)
{
	char	*new;
	int		k;
	int		len;

	len = ft_strlen(str) - i;
	k = 0;
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (NULL);
	while (k < j)
	{
		new[k] = *str;
		k++;
		str++;
	}
	str += i + 1;
	while (*str)
	{
		new[k] = *str;
		k++;
		str++;
	}
	new[k] = '\0';
	return (new);
}
