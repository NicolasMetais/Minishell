/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 13:32:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-05 13:32:09 by jbayonne         ###   ########.fr       */
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

t_cmd	*new_cmd(char *line_split, char **all_path)
{
	t_cmd	*cmd;
	char	**cmd_line_split;

	cmd_line_split = ft_split(line_split, ' ');
	if (!cmd_line_split)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free_split(cmd_line_split), NULL);
	cmd->path = get_path(cmd_line_split, all_path);
	cmd_line_split = get_fd(cmd, cmd_line_split);
	if (!cmd_line_split)
		return (free_split(cmd_line_split), NULL);
	cmd->cmd = get_cmd(cmd_line_split, all_path);
	cmd->next = NULL;
	free_split(cmd_line_split);
	return (cmd);
}

void	check_and_add_cmd_to_list(t_cmd *head, t_cmd *tmp)
{
	if (tmp->in_fd[0] == -1 || tmp->out_fd[0] == -1)
	{
		free_node(tmp);
		return ;
	}
	if (tmp->in_fd[1] > 2 || tmp->out_fd[1] > 2)
	{
		free_node(tmp);
		return ;
	}
	else
		add_back(head, tmp);
}

t_cmd	*set_cmd(char **line_split, char **env)
{
	t_cmd	*head;
	t_cmd	*tmp;
	int		i;

	i = 0;
	head = new_cmd(line_split[i], env);
	if (!head)
		return (NULL);
	i++;
	while (line_split[i])
	{
		tmp = new_cmd(line_split[i], env);
		if (!tmp)
			return (freelist(head), NULL);
		check_and_add_cmd_to_list(head, tmp);
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
	line_split = ft_split(read_line, '|');
	if (!line_split)
		return (NULL);
	glb = malloc(sizeof(t_glb));
	if (!glb)
		return (NULL);
	glb->nb_cmd = command_counter(line_split);
	glb->path = get_all_path(env);
	if (!glb->path)
		return (free_split(line_split), free(glb), NULL);
	glb->cmd = set_cmd(line_split, glb->path);
	if (!glb->cmd)
		return (free_split(line_split), free_global(glb), NULL);
	free_split(line_split);
	return (glb);
}
