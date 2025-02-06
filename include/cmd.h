/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 06:12:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/06 05:18:50 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_env	t_env;
typedef struct s_core	t_core;
typedef enum s_boolean	t_boolean;

typedef struct s_cd
{
	char		*pwd;
	char		*oldpwd;
	char		*home;
	char		**cmd;
	t_boolean	undo;
	t_boolean	ishome;
	t_boolean	ignore;
	
}	t_cd;

typedef struct s_builtin
{
	char	**cmd;
	int			arg_number;
	t_cd	cd;
}	t_builtin;

t_boolean	builtin(t_core *core);
void		env_var(t_core *core, t_builtin *builtin);
void		exit_status_display(t_core *core, t_builtin *builtin);
void		cmd_exec(t_core *core);
void		cd_init(t_core *core, t_builtin *builtin);

#endif