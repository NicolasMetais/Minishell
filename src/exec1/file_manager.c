/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:31:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/15 11:59:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	__open_infile(char *file, t_core *core)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		funct_error("minishell: ", file, core);
		core->exit_code = errno;
		return (false);
	}
	close(fd);
	return (true);
}

int	__open_outfile(t_file *tmp)
{
	if (tmp->file == 0)
		return (open(tmp->file, O_APPEND | O_WRONLY
				| O_TRUNC, 0777));
	else
		return (open(tmp->file, O_CREAT | O_WRONLY
				| O_TRUNC, 0777));
}

t_boolean	infile_manager(t_exec *exec, t_core *core)
{
	t_file	*tmp_file;
	t_cmd	*tmp_cmd;

	tmp_cmd = exec->cmd;
	while (tmp_cmd)
	{
		tmp_file = tmp_cmd->in;
		while (tmp_file)
		{	
			if (tmp_file->type == 1)
			{
				if (!__open_infile(tmp_file->file, core))
					return (false);
			}
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (true);
}


t_boolean	outfile_manager(t_exec *exec, t_core *core)
{
	t_file	*tmp_file;
	t_cmd	*tmp_cmd;
	int		fd;

	tmp_cmd = exec->cmd;
	while (tmp_cmd)
	{
		tmp_file = tmp_cmd->out;
		while (tmp_file)
		{	
			fd = __open_outfile(tmp_file);
			if (fd < 0)
			{
				funct_error("minishell: ", tmp_file->file, core);
				core->exit_code = errno;
				return (false);
			}
			close(fd);
			tmp_file = tmp_file->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (true);
}


t_boolean	parse_files(t_exec *exec, t_core *core)
{
/* 	if (exec->here_doc)
	{
		if (!here_doc_init(exec))
			return (false);
		if (!here_doc_manager(exec))
			return (false);
	} */
	if (!infile_manager(exec, core))
		return (false);
	if (!outfile_manager(exec, core))
		return (false);

	return (true);
}
