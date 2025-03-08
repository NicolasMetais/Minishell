/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:32:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/08 20:46:28 by nmetais          ###   ########.fr       */
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

char **new_cmd_file(char **cmd_line_split, t_cmd *cmd, t_red *tab_red)
{
	cmd->in = NULL;
	cmd->out = NULL;
	if (unexpected_token_red
		(get_one_line_of_cmd_split(cmd_line_split), tab_red))
		return (free(cmd), free_split(cmd_line_split), NULL);
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

	tab_red = get_tk_red(line_split);
	// if (tab_red->error == true)
	// 	return (NULL);
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

t_glb	*global_init(char *read_line, char **env)
{
	char	**line_split;
	t_glb	*glb;

	if (ft_strlen(read_line) == 0)
		return (NULL);
	line_split = get_pipe(read_line);
	if (!line_split)
		return (NULL);
	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (NULL);
	glb->nb_cmd = command_counter(line_split);
	glb->path = get_all_path(env);
	if (!glb->path)
		return (free_split(line_split), free(glb), NULL);
	glb->cmd = set_cmd(line_split);
	if (!glb->cmd)
		return (free_split(line_split), free_global(glb), NULL);
	free_split(line_split);
	return (glb);
}
