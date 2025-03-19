/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:24:46 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/19 17:30:37 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_cleanup(t_core *core, t_exec *exec)
{
	close_node_pipe(exec->here);
	free_here_doc_node(exec->here);
	core->splitted_path[0] -= 5;
	free_tab(core->splitted_path);
	kill_program(core);
	free_global(core->glb, core);
	exit(0);
}

void	print_error(void)
{
	ft_putendl_fd
		("\nminishell: warning: here-document delimited by end-of-file", 2);
}
