/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:32:22 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/15 22:20:05 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	replace_exit_code(char **tocut, int j)
{
	char	*code;
	char	*new;

	if (j < (int)ft_strlen(*tocut)
		&& (*tocut)[j + 1] == '?')
	{
		code = ft_itoa(exit_code);
		if (!code)
			return (false);
		new = write_var(code, *tocut, j, 2);
		if (!new)
			return (false);
		free(*tocut);
		(*tocut) = ft_strdup(new);
		if (!tocut)
			return (false);
		free(new);
		free(code);
	}
	return (true);
}

t_boolean	insert_del(char *data, char **tocut, int j, int i)
{
	char	*new;

	if (data)
	{
		new = write_var(data, *tocut, j, i - j);
		if (!new)
			return (false);
		free(*tocut);
		(*tocut) = ft_strdup(new);
		free(new);
		if (!tocut)
			return (false);
	}
	else
	{
		new = delete_var(*tocut, j, i - j);
		if (!new)
			return (false);
		free(*tocut);
		(*tocut) = ft_strdup(new);
		free(new);
		if (!tocut)
			return (false);
	}
	return (true);
}

t_boolean	replace_var_env(t_core *core, char **tocut, int j)
{
	int		i;
	char	*var;
	char	*data;

	i = j + 1;
	if (j < (int)ft_strlen(*tocut)
		&& ((*tocut)[j + 1] == '_' || ft_isalpha((*tocut)[j + 1])))
	{
		while ((*tocut)[i] && ((*tocut)[i] == '_' || ft_isalnum((*tocut)[i])))
			i++;
		var = ft_substr(*tocut, j + 1, i - (j + 1));
		if (!var)
			return (false);
		data = ft_get_env(core->env, var);
		free(var);
		if (!insert_del(data, tocut, j, i))
			return (free(data), false);
		free(data);
		return (true);
	}
	return (false);
}

t_boolean	var_manager(t_core *core, t_builtin *builtin)
{
	int	i;
	int	j;

	i = -1;
	while (builtin->cmd[++i])
	{
		j = -1;
		while (builtin->cmd[i][++j])
		{
			if (builtin->cmd[i][j] == '$')
			{
				if (!replace_exit_code(&builtin->cmd[i], j))
					return (false);
				if (replace_var_env(core, &builtin->cmd[i], j))
					j = -1;
				else
					return (false);
			}
		}
	}
	return (true);
}
