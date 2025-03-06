/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 02:14:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 22:46:21 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "boolean.h"

//ERROR MODULABLE PROTECTED FUNCTIONS
t_boolean	invalid_option(t_glb *global, char *cmd);
t_boolean	too_many_args(char *cmd);
t_boolean	cmd_not_found(char *cmd);
int			only_num_arg(t_glb *global, char *cmd);
int			not_valid_id(char *arg, char *cmd);
int			env_not_set(char *arg, char *cmd);

//PERROR MODULABLE
t_boolean	funct_error(char *cmd, char *addvalue);

#endif