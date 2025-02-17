/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-06 14:21:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-06 14:21:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	fd_init(t_cmd *cmd)
{
	cmd->in_fd[0] = -2;
	cmd->in_fd[1] = 0;
	cmd->out_fd[0] = -2;
	cmd->out_fd[1] = 0;
}

char	**get_infd(t_cmd *cmd, char **cmd_split)
{
	int	i;
	int	k;

	i = 0;
	while (cmd_split && cmd_split[i])
	{
		k = 1;
		if (ft_strncmp(cmd_split[i], "<", 1) == 0
			|| ft_strncmp(cmd_split[i], "<<", 2) == 0)
		{
			cmd_split = handle_in_redirection(cmd_split, cmd, i);
			if (!cmd_split)
				return (NULL);
			k = 0;
			i = 0;
		}
		if (k != 0)
			i++;
	}
	return (cmd_split);
}

char	**get_outfd(t_cmd *cmd, char **cmd_split)
{
	int	i;
	int	k;

	i = 0;
	while (cmd_split && cmd_split[i])
	{
		k = 1;
		if (ft_strncmp(cmd_split[i], ">", 1) == 0
			|| ft_strncmp(cmd_split[i], ">>", 2) == 0)
		{
			fprintf(stderr, "%s, %s \n", cmd_split[i], cmd_split[i + 1]);
			cmd_split = realloc_fd_out(cmd, cmd_split, i);
			k = 0;
			i = 0;
		}
		if (k != 0)
			i++;
	}
	return (cmd_split);
}

char	**get_fd(t_cmd *cmd, char **cmd_line_split)
{
	char	**tmp;

	fd_init(cmd);
	cmd->here_doc = NULL;
	tmp = get_infd(cmd, cmd_line_split);
	if (!cmd_line_split)
		return (NULL);
	cmd_line_split = get_outfd(cmd, tmp);
	if (!cmd_line_split)
		return (NULL);
	return (cmd_line_split);
}
