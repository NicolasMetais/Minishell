/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:32:22 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/04 15:49:12 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE PRINT L'EXIT CODE A LA PLACE DE $? DANS TOUTES LES STRINGS DU SHELL
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
		if (!insert_del(data, tocut, j, i))
			return (free(var), free(data), false);
		return (free(var), free(data), true);
	}
	if (j < (int)ft_strlen(*tocut) && ft_isdigit((*tocut)[j + 1]))
	{
		if (!insert_del(NULL, tocut, j, j + 2))
			return (false);
		return (true);
	}
	return (false);
}

//EXTENSION DE VARIABLE $? et $VARIABLE
char	**var_manager(t_core *core, char **new_line, t_boolean *replace)
{
	int	i;
	int	j;

	i = -1;
	while (new_line[++i])
	{
		j = -1;
		while (new_line[i][++j])
		{
			if (new_line[i][j] == '$')
			{
				if (replace_exit_code(&new_line[i], j)
					|| replace_var_env(core, &new_line[i], j))
				{
					j = -1;
					*replace = true;
				}
			}
		}
	}
	return (new_line);
}

t_boolean	setup_var(t_core *core)
{
	t_boolean	replace;
	int			i;
	int			j;
	int			count;

	count = 0;
	replace = false;
	core->new_line = ft_split(core->line, ' ');
	if (!core->new_line)
		return (false);
	core->new_line = var_manager(core, core->new_line, &replace);
	i = 0;
	while (core->new_line[i])
	{
		j = 0;
		while (core->new_line[i][j])
			j++;
		count += j;
		i++;
	}
	rewrite_line(core, i, count);
	free_tab(core->new_line);
	return (true);
}
