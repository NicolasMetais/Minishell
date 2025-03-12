/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:11:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/12 22:43:33 by jbayonne         ###   ########.fr       */
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

void	execve_error(t_core *core, t_exec *exec)
{
	if (core->errorno == ENOENT)
		cmd_not_found(exec->cmd->args[0], core);
	else if (core->errorno == EACCES)
		permission_denied(exec->cmd->args[0], core);
	else
	{
		core->exit_code = core->errorno;
		perror("minishell");
	}
	exit(core->exit_code);
}

t_boolean	exec_shell(t_exec *exec, char *slash, t_core *core)
{
	int		checker;
	char	*tester;
	int		j;

	j = -1;
	(void)core;
	while (exec->env_path[++j])
	{
		if (!exec->absolute_path)
		{
			tester = ft_strjoin(exec->env_path[j], slash);
			if (!tester)
				return (false);
		}
		else
			tester = slash;
		checker = access(tester, F_OK | X_OK);
		if (checker == 0)
			execve(tester, exec->cmd->args, exec->env);
		if (!exec->absolute_path)
			free(tester);
	}
	return (free(slash), false);
}

int	env_exec(t_exec *exec, t_core *core)
{
	char	*slash;

	if (!exec->cmd->args[0])
		exit(0);
	if (!absolute_path(exec, exec->cmd->args[0]))
	{
		slash = ft_strjoin("/", exec->cmd->args[0]);
		if (!slash)
			return (false);
		exec_shell(exec, slash, core);
	}
	else
	{
		exec_shell(exec, exec->cmd->args[0], core);
	}
	core->errorno = errno;
	execve_error(core, exec);
	return (core->exit_code);
}
