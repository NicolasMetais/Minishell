/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:23:47 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-10 14:23:47 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	pipe_error(t_pipe_token *pipe, char *str)
{
	if (pipe->next)
		pipe = pipe->next;
	str++;
	while (*str && (*str == ' ' && (*str != '\'' && *str != '"')))
		str++;
	if (!*str)
		return (false);
	if (*str == '|' && pipe->valid == true)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	if (*str == '|' && !(str + 1))
	{
		ft_printf("minishell: missing command\n");
		return (true);
	}	
	return (false);
}

t_boolean	redirection_error(t_pipe_token *pipe, t_red *red, char *str)
{
	char	c;

	str++;
	if (red->next)
		red = red->next;
	while (*str && (*str == ' ' && (*str != '\'' && *str != '"')))
		str++;
	if (!*str)
		return (false);
	if (is_redirection_char(*str) && red->valid == true)
	{	
		c = *str;
		if (red->type == double_)
			ft_printf("minishell: syntax error near unexpected token `%c%c'\n",
				c, c);
		else
			ft_printf("minishell: syntax error near unexpected token `%c'\n", c);
		return (true);
	}
	if (*str == '|' && pipe->valid == true)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	return (false);
}

t_boolean	token_error(t_pipe_token *pipe, t_red *red, char *str)
{
	t_bool_pipe	var;

	init_var_token_error(&var, str);
	if (!var.word)
		return (true);
	while (*var.word)
	{
		if (*var.word == var.c)
			turn_false_tok_error(&var);
		if (var.c == 0 && (*var.word == '\'' || *var.word == '"'))
			turn_true_tok_error(&var);
		if (*var.word == '|' && pipe->valid == true && var.quote == false)
		{
			if (pipe_error(pipe, str))
				return (true);
		}
		if (is_redirection_char(*var.word) && var.quote == false)
		{
			if (is_red_error(pipe, red, &var))
				return (true);
		}		
		var.word++;
	}
	return (false);
}

t_boolean	handle_token_error(char *readline)
{
	t_red			*tk_red;
	t_pipe_token	*tk_pipe;
	char			*str;

	str = ft_strdup(readline);
	if (!str)
		return (true);
	tk_red = get_tk_red(readline);
	tk_pipe = get_tk_pipe(readline);
	if (token_error(tk_pipe, tk_red, str))
		return (true);
	free(str);
	return (false);
}
