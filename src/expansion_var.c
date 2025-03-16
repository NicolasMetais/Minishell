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

char	*get_variable_utils(char *old, t_core *core, int i)
{
	char	*var;
	char	*tmp;
	char	*new;

	tmp = ft_strndup(core->line, i);
	if (!tmp)
		return (free(old), NULL);
	if (*tmp == '?')
	{
		var = ft_strdup(ft_itoa(core->exit_code));
		if (!var)
			return (NULL);
	}
	else
		var = ft_get_env(core->env, tmp);
	free(tmp);
	new = ft_strjoin_custom(old, var);
	free(var);
	if (!new)
		return (free(old), NULL);
	return (new);
}

char	*get_variable(char *old, t_core *core, t_tk_dollar *dollar)
{
	char	*new;
	int		i;

	i = 0;
	core->line++;
	if (dollar->valid == true && (ft_isalpha(*core->line) || *core->line == '_' 
		|| *core->line == '?'))
	{
		if (*core->line == '?')
		{
			core->line++;
			i++;	
		}
		else
		{
			while(*core->line && (ft_isalnum(*core->line) || *core->line == '_'))
			{
					core->line++;
					i++;
			}
		}	
		new = get_variable_utils(old, core, i);
		if (!new)
			return (NULL);
		return (free(old), new);
	}
	else
	{
		core->line--;
		return (old);
	}
}

char	*dynamic_copy(char *old, char c)
{
	int		i;
	int		len;
	char	*new;
	
	i = 0;
	len =  ft_strlen(old);
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(old);
	return (new);
}

void	init_var_expand(t_expand_var *ctx)
{
	ctx->error = 0;
	ctx->tmp = NULL;
	ctx->new_line = NULL;
}

char	*expansion_var(t_core *core)
{
	t_tk_dollar		*dollar;
	t_expand_var	ctx;

	init_var_expand(&ctx);
	dollar = get_tk_dollar(core->line, &ctx.error);
	if (ctx.error == 1)
		return (NULL);
	ctx.new_line = NULL;
	while (*core->line)
	{
		ctx.tmp = ctx.new_line;
		if (*core->line == '$')
		{
			ctx.new_line = get_variable(ctx.new_line, core, dollar);
			if (!ctx.new_line)
				return (free(ctx.tmp), NULL);
			dollar = dollar->next;
		}
		ctx.new_line = dynamic_copy(ctx.new_line, *core->line);
		if (!ctx.new_line)
			return (free(ctx.tmp), NULL);
		if (!*core->line)
			break ;
		core->line++;
	}
	return (ctx.new_line);
}