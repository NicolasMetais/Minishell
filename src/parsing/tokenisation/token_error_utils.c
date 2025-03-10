/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 19:59:28 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-10 19:59:28 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var_token_error(t_bool_pipe *var, char *str)
{
	var->c = 0;
	var->quote = false;
	var->word = ft_strdup(str);
	var->tmp = var->word;
}

void	turn_false_tok_error(t_bool_pipe *var)
{
	var->quote = false;
	var->c = 0;
	var->word++;
}

void	turn_true_tok_error(t_bool_pipe *var)
{
	var->quote = true;
	var->c = 0;
	var->word++;
}

t_boolean	is_red_error(t_pipe_token *pipe, t_red *red, t_bool_pipe *ctx)
{
	if (red->type == double_)
		ctx->word++;
	if (redirection_error(pipe, red, ctx->word))
		return (true);
	return (false);
}

void	free_pipe_tk(t_pipe_token *tk)
{
	t_pipe_token	*tmp;

	while (tk)
	{
		tmp = tk->next;
		free(tk);
		tk = tmp;
	}
}
