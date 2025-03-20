/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:11:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/20 00:32:14 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	absolute_path(t_exec *exec, char *to_check)
{
	int	i;

	i = 0;
	while (to_check[i])
	{
		if (to_check[i] == '.' || to_check[i] == '/')
		{
			exec->absolute_path = true;
			return (true);
		}
		i++;
	}
	return (false);
}

int	is_directory(const char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
		return (S_ISDIR(buf.st_mode));
	return (0);
}

void	execve_error(t_core *core, t_exec *exec, char *tmp)
{
	if (only_point(tmp))
		file_name_argument(tmp, core);
	else if (is_directory(exec->cmd->args[0]) > 0)
	{
		core->errorno = errno;
		error_directory(tmp, core);
	}
	else if (core->errorno == ENOENT)
		cmd_not_found(tmp, core);
	else if (core->errorno == EACCES)
		permission_denied(tmp, core);
	else
	{
		core->exit_code = core->errorno;
		perror("minishell");
	}
	if (exec->nb_cmd > 1)
		free_pipe(exec->nb_cmd - 1, exec->pipe);
	kill_program(core);
	free_random(exec, core);
	free_global(core->glb, NULL);
	exit(core->exit_code);
}

t_boolean	exec_shell(t_exec *exec, char *slash, t_core *core)
{
	int		checker;
	char	*tester;
	int		j;

	j = -1;
	while (core->splitted_path[++j])
	{
		if (!exec->absolute_path)
		{
			tester = ft_strjoin(core->splitted_path[j], slash);
			if (!tester)
				return (false);
		}
		else
			tester = slash;
		checker = access(tester, F_OK | X_OK);
		if (checker == 0)
		{
			execve(tester, exec->cmd->args, exec->env);
		}
		if (!exec->absolute_path)
			free(tester);
	}
	return (false);
}

int	env_exec(t_exec *exec, t_core *core)
{
	char	*slash;
	char	*tmp;

	slash = NULL;
	tmp = ft_strdup(exec->cmd->args[0]);
	if (!tmp)
		core->errorno = ENOBUFS;
	if (ft_strlen(exec->cmd->args[0]) == 0)
		core->errorno = ENOENT;
	else if (!absolute_path(exec, exec->cmd->args[0]))
	{
		slash = ft_strjoin("/", exec->cmd->args[0]);
		if (!slash)
			return (false);
		exec_shell(exec, slash, core);
	}
	else
		exec_shell(exec, exec->cmd->args[0], core);
	core->errorno = errno;
	free(slash);
	slash = NULL;
	execve_error(core, exec, tmp);
	return (free(tmp), core->exit_code);
}
