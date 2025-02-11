/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 17:25:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-09 17:25:55 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_heredoc(char **cmd_split, t_cmd *cmd, int i)
{
	if (cmd->here_doc != NULL)
		free(cmd->here_doc);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (NULL);
	cmd->here_doc = ft_strdup(cmd_split[i]);
	if (!cmd->here_doc)
		return (NULL);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (NULL);
	return (cmd_split);
}

char	**handle_in_redirection(char **cmd_split, t_cmd *cmd, int i)
{
	if (ft_strlen(cmd_split[i]) == 2)
	{
		cmd_split = handle_heredoc(cmd_split, cmd, i);
		if (!cmd_split)
			return (NULL);
		return (cmd_split);
	}
	else
	{	
		cmd_split = realloc_fd_in(cmd, cmd_split, i);
		if (!cmd_split)
			return (NULL);
		return (cmd_split);
	}
	return (NULL);
}
