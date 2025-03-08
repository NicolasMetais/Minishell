/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_token_redirection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-05 16:56:57 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-05 16:56:57 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	error_token_red(char *cmd_one_line, t_red *tab_red)
{
	char	c;
	int		i;

	i = 0;
	c = *cmd_one_line;
	if (tab_red->type == double_)
		ft_printf("minishell: syntax error near unexpected token `%c%c'\n", c, c);
	else
		ft_printf("minishell: syntax error near unexpected token `%c'\n", c);
}

t_boolean	unexpected_token_red(char *cmd_one_line, t_red *tab_red)
{
	int		i;
	t_red	*tmp;
	char	*fstr;

	i = 0;
	tmp = tab_red;
	fstr = cmd_one_line;
	while (*cmd_one_line)
	{
		if (is_redirection_char(*cmd_one_line) && tmp->valid == true)
		{
			if (tmp->type == double_)
				cmd_one_line++;
			cmd_one_line++;
			tmp = tmp->next;
			if (is_redirection_char(*cmd_one_line) && tmp->valid == true)
				return(error_token_red(cmd_one_line, tmp), free(fstr), true);
		}
		cmd_one_line++;
	}
	return (free(fstr), false);
}