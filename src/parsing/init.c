/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:32:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/12 22:29:13 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_cmd *head, t_cmd *new)
{
	t_cmd	*tmp;

	if (head == NULL)
	{
		head = new;
		tmp = NULL;
		return ;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp = NULL;
	return ;
}

char	**new_cmd_file(char **cmd_line_split, t_cmd *cmd, t_red *tab_red)
{
	cmd->in = NULL;
	cmd->out = NULL;
	if (tab_red)
	{
		cmd_line_split = get_fd(cmd, cmd_line_split, tab_red);
		if (!cmd_line_split)
			return (free(cmd), NULL);
		free_tab_red(tab_red);
	}
	return (cmd_line_split);
}

t_cmd	*new_cmd(char *line_split)
{
	t_cmd	*cmd;
	t_red	*tab_red;
	char	**cmd_line_split;
	int		error;

	error = 0;
	tab_red = get_tk_red(line_split, &error);
	if (error == 1)
		return (NULL);
	cmd_line_split = get_quote_dup(line_split);
	if (!cmd_line_split)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free_split(cmd_line_split), NULL);
	cmd->args = new_cmd_file(cmd_line_split, cmd, tab_red);
	if (!cmd->args)
		return (NULL);
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*set_cmd(char **line_split)
{
	t_cmd	*head;
	t_cmd	*tmp;
	int		i;

	i = 0;
	head = new_cmd(line_split[i]);
	if (!head)
		return (NULL);
	i++;
	while (line_split[i])
	{
		tmp = new_cmd(line_split[i]);
		if (!tmp)
			return (freelist(head), NULL);
		add_back(head, tmp);
		i++;
	}
	return (head);
}

t_glb	*global_init(t_core *core)
{
	char	**line_split;
	t_glb	*glb;
	int		error;

	error = 0;
	if (ft_strlen(core->line) == 0)
		return (NULL);
	if (handle_token_error(core->line, &error))
	{
		core->exit_code = 2;
		return (NULL);
	}
	line_split = get_pipe(core->line);
	if (!line_split)
		return (NULL);
	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (NULL);
	glb->nb_cmd = command_counter(line_split);
	glb->cmd = set_cmd(line_split);
	if (!glb->cmd)
		return (free_split(line_split), free(glb), NULL);
	glb->all_in = get_all_in(glb->cmd);
	glb->all_out = get_all_out(glb->cmd);
	return (free_split(line_split),	glb);
}
