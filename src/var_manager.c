/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:32:22 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/12 22:23:05 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_var(char *tocut, int start, int end)
{
	char	*new;
	int		i;
	int		j;

	printf("start: %d end : %d\n", start, end);
	new = malloc(sizeof(char) * (ft_strlen(tocut) - (start - end) + 1));
	if (!new)
		return (NULL);
	j = 0;
	i = 0;
	while (tocut[j])
	{
		if (j == start)
			j += end;
		new[i] = tocut[j];
		i++;
		j++;
	}
	new[i] = '\0';
	printf("data %s\n", new);
	return (new);
}

char	*write_var(char *code, char *tocut, int j, int size)
{
	char	*new;
	int		i;
	int		l;
	int		k;

	i = 0;
	l = 0;
	k = 0;
	new = malloc(sizeof(char) * (ft_strlen(code)
				+ (ft_strlen(tocut) - size) + 1));
	if (!new)
		return (NULL);
	while (tocut[i])
	{
		if (i == j)
		{
			while (code[k])
				new[l++] = code[k++];
			i += size;
		}
		else
			new[l++] = tocut[i++];
	}
	new[l] = '\0';
	return (new);
}

t_boolean	replace_exit_code(char **tocut, int j)
{
	char	*code;
	char	*new;

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
	return (true);
}

t_boolean	replace_var_env(t_core *core, char **tocut, int j)
{
	int		i;
	char	*var;
	char	*data;
	char	*new;

	i = j + 1;
	if (((*tocut)[i] == '_' || ft_isalpha((*tocut)[i])))
	{
		while ((*tocut)[i] && ((*tocut)[i] == '_' || ft_isalnum((*tocut)[i])))
			i++;
		var = ft_substr(*tocut, j + 1, i - (j + 1));
		if (!var)
			return (false);
		data = ft_get_env(core->env, var);
		if (data)
		{
			new = write_var(data, *tocut, j, i - j);
			if (!new)
				return (false);
			free(*tocut);
			(*tocut) = ft_strdup(new);
			if (!tocut)
				return (false);
			free(new);
		}
		else
		{
			new = delete_var(*tocut, j, i - j);
			free(*tocut);
			(*tocut) = ft_strdup(new);
			free(new);
		}
	}
	return (true);
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
				if (j < (int)ft_strlen(builtin->cmd[i])
					&& builtin->cmd[i][j + 1] == '?')
					replace_exit_code(&builtin->cmd[i], j);
				if (j < (int)ft_strlen(builtin->cmd[i]))
					replace_var_env(core, &builtin->cmd[i], j);
			}
		}
	}
	return (true);
}
