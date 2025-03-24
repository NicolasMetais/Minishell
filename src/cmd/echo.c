/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:46:08 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/24 12:18:52 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_writted(int value, t_core *core)
{
	if (value < 0)
	{
		ft_putendl_fd
			("minishell: echo: write error: No space left on device", 2);
		core->exit_code = 1;
		return (true);
	}
	return (false);
}

//GESTION DU FLAG -N QUI PREND EN COMPTE LES MULTIPLE -N ET -NNNNN..
int	flag_check(t_cmd *cmd, t_boolean *flag)
{
	int	j;
	int	i;
	int	valid;

	i = 1;
	if (cmd->args_nb == 1)
		return (i);
	valid = 0;
	while (cmd->args[i]
		&& ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		j = 1;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] != 'n')
				return (i);
			j++;
		}
		valid++;
		*flag = true;
		i++;
	}
	return (i);
}

t_boolean	echo_next(t_cmd *cmd, t_core *core, int size, int *i)
{
	int	value;

	value = 0;
	while (cmd->args[*i])
	{
		value = printf("%s", cmd->args[*i]);
		if (is_writted(value, core))
			return (true);
		(*i)++;
		if (*i < size)
			value = printf(" ");
		if (is_writted(value, core))
			return (true);
	}
	return (true);
}

//PRINTF POUR EXEC ECHO
t_boolean	echo_init(t_cmd *cmd, t_core *core)
{
	int			size;
	int			i;
	t_boolean	flag;
	int			value;

	size = 0;
	value = 0;
	flag = false;
	i = flag_check(cmd, &flag);
	while (cmd->args[size])
		size++;
	echo_next(cmd, core, size, &i);
	if (!flag)
	value = printf("\n");
	if (is_writted(value, core))
		return (true);
	return (true);
}
