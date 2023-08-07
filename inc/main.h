/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:33:51 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/14 14:42:03 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"
# include "tokenizer.h"

void	sigint_reprompt(int signo);
void	empty_sighandler(int signo);

int		init(t_env **env, char **envp, char **buf, char **argv);

void	prompt(char **buf, t_env *env);
void	execute(t_env *env, char *buf);
int		parse(t_env	*env, char *input);

#endif