/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:44 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/04 01:23:32 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

typedef struct s_pipex
{
	char		***cmd;
	char		**env;
	char		**av;
	char		**env_path;
	char		*limiter;
	int			fork_count;
	int			pipe_fd[2];
	int			ac;
	int			infile_fd;
	int			outfile_fd;
	pid_t		pid;
	int			input_fd;
	t_boolean	absolute_path;
	t_boolean	here_doc;
}	t_pipex;

void		free_all(t_pipex *pipex);

t_boolean	env_parse(t_pipex *pipex);
t_boolean	args_parse(t_pipex *pipex);

int			env_exec(t_pipex *pipex, int i);
t_boolean	fork_process(t_pipex *pipex, pid_t pid, int i);
void		fd_setup(t_pipex *pipex, int *pipe_fd, int i);

void		here_doc(t_pipex *pipex);
t_boolean	core(t_pipex *pipex);

#endif
