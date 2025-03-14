/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 02:10:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/13 18:02:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE PRINT L'EXIT CODE A LA PLACE DE $? DANS TOUTES LES STRINGS DU SHELL
t_boolean	replace_exit_code(char **tocut, int j, t_core *core)
{
	char	*code;
	char	*new;

	if (j < (int)ft_strlen(*tocut)
		&& (*tocut)[j] == '?')
	{
		code = ft_itoa(core->exit_code);
		if (!code)
			return (false);
		new = write_var(code, *tocut, j, 1);
		if (!new)
			return (false);
		free(*tocut);
		(*tocut) = ft_strdup(new);
		if (!tocut)
			return (false);
		free(new);
		free(code);
		core->exit_code = 0;
		return (true);
	}
	else
		return (false);
}

//JE DECIDE SI J'ECRIS OU SI JE DELETE LA VAR
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

//JE VERIFIE QUE LA VAR EST DE LA BONNE FORME
t_boolean	replace_var_env(t_core *core, char **tocut, int j)
{
	int		i;
	char	*var;
	char	*data;

	i = 0;
	if (j < (int)ft_strlen(*tocut)
		&& ((*tocut)[j] == '_' || ft_isalpha((*tocut)[j])))
	{
		while ((*tocut)[i] && ((*tocut)[i] == '_' || ft_isalnum((*tocut)[i])))
			i++;
		var = ft_substr(*tocut, j, i - j);
		if (!var)
			return (false);
		data = ft_get_env(core->env, var);
		if (!insert_del(data, tocut, j, i))
			return (free(var), free(data), false);
		return (free(var), free(data), true);
	}
	if (j < (int)ft_strlen(*tocut) && ft_isdigit((*tocut)[j]))
	{
		if (!insert_del(NULL, tocut, j, j + 1))
			return (false);
		return (true);
	}
	return (false);
}


char	**expansion_manager(t_core *core, char **new_line, int *pos)
{
	int	i;

	if (pos[0] == 0)
		i = 0;
	else
		i = 1;
	while (new_line[i])
	{
		if (!replace_exit_code(&new_line[i], 0, core))
		{
			if (!replace_var_env(core, &new_line[i], 0))
				return (NULL);
		}
		i++;
	}
	return (new_line);
}

int	expansion_var(t_core *core)
{
	int	*pos;
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	pos = NULL;
	pos = is_dollar(core, pos);
	if (!pos)
		return (2);
	core->new_line = ft_split(core->line, '$');
	if (!core->new_line)
		return (free(pos), 0);
	core->new_line = expansion_manager(core, core->new_line, pos);
	while (core->new_line[++i])
	{
		j = 0;
		while (core->new_line[i][j])
			j++;
		count += j;
	}
	rewrite_line(core, i, count);
	free_tab(core->new_line);
	return (free(pos), 1);
}
