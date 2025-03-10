/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 21:11:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/09 22:06:50 by nmetais          ###   ########.fr       */
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

void	execve_error(t_core *core)
{
	perror("Minishell");
	core->exit_code = errno;
	exit(errno);
}

t_boolean	exec_shell(t_exec *exec, char *slash, t_core *core)
{
	int		checker;
	char	*tester;
	int		j;

	j = 0;
	while (exec->env_path[j])
	{
		if (!exec->absolute_path)
		{
			tester = ft_strjoin(exec->env_path[j], slash);
			if (!tester)
				return (false);
		}
		else
			tester = slash;
		checker = access(tester, F_OK);
		if (checker == 0)
		{
			if (execve(tester, exec->cmd->args, exec->env) == -1)
				execve_error(core);
		}
		j++;
	}
	return (false);
}

int	env_exec(t_exec *exec, t_core *core)
{
	char	*slash;
	int		status;

	if (!absolute_path(exec, exec->cmd->args[0]))
	{
		slash = ft_strjoin("/", exec->cmd->args[0]);
		if (!slash)
			return (false);
		status = exec_shell(exec, slash, core);
	}
	else
		status = exec_shell(exec, exec->cmd->args[0], core);
	perror("Minishellu");
	core->exit_code = errno;
	return (core->exit_code);
}
