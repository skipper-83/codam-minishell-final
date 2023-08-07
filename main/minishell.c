/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 12:40:44 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/04 19:48:46 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_env		*env;

	(void)argc;
	if (!init(&env, envp, &buf, argv))
		exit (EXIT_FAILURE);
	while (buf != NULL)
	{
		execute(env, buf);
		prompt(&buf, env);
	}
	exit_ceash(env, NULL);
}
