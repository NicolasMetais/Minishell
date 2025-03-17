/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:23:47 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:48:17 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	pipe_error(t_pipe_token *pipe, char *str, char *tmp)
{
	if (*tmp == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (true);
	}
	if (pipe->next)
		pipe = pipe->next;
	str++;
	while (*str && (*str == ' ' && (*str != '\'' && *str != '"')))
		str++;
	if (!*str)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		return (true);
	}
	if (*str == '|' && pipe->valid == true)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (true);
	}
	return (false);
}

void	redirection_error_2(t_red *red, char *str)
{
	char	c;

	c = *str;
	if (red->type == double_)
		ft_printf("minishell: syntax error near unexpected token `%c%c'\n",
			c, c);
	else
		ft_printf("minishell: syntax error near unexpected token `%c'\n", c);
}

t_boolean	redirection_error(t_pipe_token *pipe, t_red **red, char *str)
{
	str++;
	if ((*red)->next)
		*red = (*red)->next;
	while (*str && (*str == ' ' && (*str != '\'' && *str != '"')))
		str++;
	if (!*str)
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (true);
	}
	if (is_redirection_char(*str) && (*red)->valid == true)
	{	
		redirection_error_2(*red, str);
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
	t_bool_pipe		var;

	init_var_token_error(&var, str);
	if (!var.word)
		return (true);
	while (*var.word)
	{
		turn_token_error(&var);
		if (*var.word == '|' && pipe->valid == true && var.quote == false)
		{
			if (pipe_error(pipe, var.word, str))
				return (free(var.tmp), true);
		}
		if (is_redirection_char(*var.word) && var.quote == false)
		{
			if (is_red_error(pipe, &red, &var))
				return (free(var.tmp), true);
		}
		if (ft_strlen(var.word) == 0)
			break ;
		var.word++;
	}
	return (free(var.tmp), false);
}

t_boolean	handle_token_error(char *readline, int *error)
{
	t_red			*tk_red;
	t_red			*red_tmp;
	t_pipe_token	*tk_pipe;
	t_pipe_token	*pipe_tmp;
	char			*str;

	str = ft_strdup(readline);
	if (!str)
		return (true);
	tk_red = get_tk_red(readline, error);
	if (*error == 1)
		return (true);
	tk_pipe = get_tk_pipe(readline, error);
	if (*error == 1)
		return (true);
	red_tmp = tk_red;
	pipe_tmp = tk_pipe;
	if (token_error(tk_pipe, tk_red, str))
		return (free(str), free_pipe_tk(pipe_tmp), free_tab_red(red_tmp), true);
	if (quote_error(str))
		return (free(str), free_pipe_tk(pipe_tmp), free_tab_red(red_tmp), true);
	free(str);
	free_pipe_tk(pipe_tmp);
	free_tab_red(red_tmp);
	return (false);
}