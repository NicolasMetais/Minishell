/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:46 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/23 16:49:37 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_cleanup(t_core *core, t_exec *exec)
{
	(void)core;
	close_node_pipe(exec->here);
	free(exec->pipe_here_doc);
	free_here_doc_node(exec->here);
}

void	print_error(void)
{
	ft_putendl_fd
		("minishell: warning: here-document delimited by end-of-file", 2);
}
