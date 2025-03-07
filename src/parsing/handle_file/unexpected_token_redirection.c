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
	t_red	*tmp;

	i = 0;
	c = *cmd_one_line;
	tmp = tab_red;
	while (*cmd_one_line == c && tmp->valid == true)
	{	
		i++;
		tmp = tmp->next;
	}
	if (i > 2)
		ft_printf("minishell: syntax error near unexpected token `%c%c'", c, c);
	else
		ft_printf("minishell: syntax error near unexpected token `%c'", c);
}

t_boolean	unexpected_token_red(char *cmd_one_line, t_red *tab_red)
{
	int		i;
	t_red	*tmp;

	i = 0;
	tmp = tab_red;
	while (*cmd_one_line)
	{
		if (is_redirection_char(*cmd_one_line) && tmp->valid == true)
		{
			if (tmp->type == double_)
				cmd_one_line++;
			cmd_one_line++;
			tmp = tmp->next;
			if (is_redirection_char(*cmd_one_line) && tmp->valid == true)
				return(error_token_red(cmd_one_line, tmp), true);
		}
		cmd_one_line++;
	}
	return (false);
}