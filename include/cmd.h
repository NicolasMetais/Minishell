/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 06:12:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 21:54:36 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_env	t_env;
typedef struct s_core	t_core;
typedef enum s_boolean	t_boolean;

typedef struct s_gc
{
	void		*data;
	struct s_gc	*next;
}	t_gc;

typedef struct s_cd
{
	char		*pwd;
	char		*oldpwd;
	char		*home;
	t_boolean	undo;
	t_boolean	ishome;
}	t_cd;

typedef struct s_builtin
{
	char	**cmd;
	int		arg_number;
	t_cd	cd;
}	t_builtin;



//TEMP
void		cmd_exec(t_core *core);

//BUILTIN
int			builtin(t_core *core);
void		env_var(t_core *core, t_builtin *builtin);
void		exit_status_display(t_core *core, t_builtin *builtin);
t_boolean	cd_init(t_core *core, t_builtin *builtin);
t_boolean	echo_init(t_builtin *builtin);

//GARBAGE COLLECTOR
void		add_to_gc(t_gc **gc, void *data);
void		*gc_malloc(t_gc	**gc, unsigned int size);
void		free_gc(t_gc *gc);

#endif