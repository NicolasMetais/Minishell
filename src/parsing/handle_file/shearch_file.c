/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearch_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-08 12:14:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-08 12:14:24 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*un_next(t_cmd *cmd, char *str, t_red *tab_red, t_un_word_var *var)
{
	char    *file;

	file = ft_strndup(str, var->i);
	if (!file)
		return (free(var->tmp), NULL);
	add_file_to_cmd(file, var->c, cmd, tab_red, 1);
	if (cmd->error == 1)
		return (free(var->tmp), NULL);
	if (tab_red->type == double_)
		var->i++;
	str = realloc_str_file(var->tmp, var->i, var->j);
	if (!str)
		return (free(var->tmp), NULL);
	return (str);
}

void    t_un_word_var_init(t_un_word_var *var, char *str)
{
	var->i = 0;
	var->tmp = str;
	var->j = 0;
}

char	*handle_cmd_file_word_un(t_cmd *cmd, char *str, t_red **tab_red)
{
	t_un_word_var   var;
	t_red			*tmp_red;

	tmp_red = *tab_red;
	t_un_word_var_init(&var, str);
	while (*str && !is_redirection_char(*str))
	{
		str++;
		var.j++;
	}
	var.c = *str;
	if ((*tab_red)->type == double_)
		str++;
	str++;
	if ((*tab_red)->next)
		*tab_red = (*tab_red)->next;
	while (*str && !(is_redirection_char(*str) && (*tab_red)->valid == true))
	{	
		if (is_redirection_char(*str) && (*tab_red)->valid == false)
		{
			if ((*tab_red)->type == double_)
			{
				var.i++;
				str++;
			}
			*tab_red = (*tab_red)->next;
		}
		str++;
		var.i++;
	}
	str = un_next(cmd, str, tmp_red, &var);
	if (!str)
		return (NULL);
	return (free(var.tmp), str);
}

char	*handle_cmd_file_word_deux(char c, t_cmd *cmd, char *str, t_red **tab_red)
{
	char	*file;
	char	*tmp;
	t_red	*tmp_red;
	int		i;

	i = 0;
	tmp = str;
	tmp_red = *tab_red;
	if ((*tab_red)->next)
		*tab_red = (*tab_red)->next;
	while (*str && !(is_redirection_char(*str) && (*tab_red)->valid == true))
	{	
		if (is_redirection_char(*str) && (*tab_red)->valid == false)
		{
			if ((*tab_red)->type == double_)
			{
				i++;
				str++;
			}
			*tab_red = (*tab_red)->next;
		}
		str++;
		i++;
	}
	file = ft_strndup(str, i);
	add_file_to_cmd(file, c, cmd, tmp_red, 1);
	if (cmd->error == 1)
		return (free(tmp), NULL);
	str = realloc_line(tmp, i, NULL);
	if (!str)
		return (free(tmp), NULL);
	return (free(tmp), str);
}