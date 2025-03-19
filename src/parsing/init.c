/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:32:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 16:39:05 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_cmd_file(char **cmd_line_split, t_cmd *cmd, t_red *tab_red)
{
	char	**tmp;

	cmd->in = NULL;
	cmd->out = NULL;
	tmp = cmd_line_split;
	printf("tmp1 add : %p\n", tmp);
	printf("tmp1 bis add : %p\n", *tmp);
	if (tab_red)
	{
		cmd_line_split = get_fd(cmd_line_split, cmd, tab_red);
		if (!cmd_line_split)
			return (free(cmd), NULL);
		free_tab_red(tab_red);
	}
	printf("tmp2 add : %p\n", tmp);
	printf("tmp2 bis add : %p\n", *tmp);
	free_split(tmp);
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
	cmd->is_a_directory = is_a_directory(cmd->args[0]);
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

t_boolean	check_error(t_core *core)
{
	int	error;

	error = 0;
	if (ft_strlen(core->line) == 0)
		return (true);
	if (handle_token_error(core->line, &error))
	{
		core->exit_code = 2;
		return (true);
	}
	return (false);
}

t_glb	*global_init(t_core *core)
{
	char	**line_split;
	t_glb	*glb;
	char	*tmp;

	tmp = core->line;
	if (check_error(core))
		return (NULL);
	core->line = expansion_var(core);
	if (!core->line)
		return (NULL);
	free(tmp);
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
	the_arno(glb);
	return (free_split(line_split), glb);
}
