/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 02:14:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/07 03:26:12 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

//ERROR MODULABLE PROTECTED FUNCTIONS
t_boolean	invalid_option(t_builtin *builtin, char *cmd);
t_boolean	too_many_args(char *cmd);
//PERROR MODULABLE
t_boolean	funct_error(char *cmd, char *addvalue);

#endif