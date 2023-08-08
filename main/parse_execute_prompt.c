/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute_prompt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:40:26 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/08 13:22:46 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main.h"

int	parse(t_env	*env, char *input)
{
	t_token_lst	tok_list;

	make_token_list(&tok_list, input, ft_strlen(input));
	add_history(input);
	free (input);
	if (tok_list.head == NULL)
		return (0);
	env->cmd_list = make_command_list(&tok_list);
	if (env->cmd_list == NULL)
		return (env->last_exit = 0, 0);
	if (!parse_quotes(env))
		return (0);
	if (env->cmd_list == NULL)
		return (env->last_exit = 0, 0);
	if (!parse_command_list(env->cmd_list, env))
		return (0);
	if (!check_conditions(env->cmd_list, NULL, 0))
		return (0);
	return (1);
}

void	prompt(char **buf, t_env *env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_reprompt);
	rl_replace_line("", 0);
	rl_on_new_line();
	*buf = readline(get_env_value(env->env_vars, "PS1"));
	signal(SIGINT, SIG_IGN);
}

void	execute(t_env *env, char *buf)
{
	int	retval;

	if (parse(env, buf))
	{
		signal(SIGINT, empty_sighandler);
		signal(SIGQUIT, empty_sighandler);
		env->cmd_tree = make_command_tree(env->cmd_list);
		if (env->cmd_tree != NULL)
		{
			if (env->verbose)
				ft_btree_print(env->cmd_tree, get_cmd_literal, 12, 6);
			if ((env->hdocs && env->hdocs->content))
				redir_heredoc(env);
			retval = execute_command_tree(env->cmd_tree, env);
			env->last_exit = retval;
			close_fds(env);
			close_hdocs(env);
			ft_btree_free(&env->cmd_tree, NULL);
		}
	}
	ft_lstclear(&env->open_fds, NULL);
	ft_lstclear(&env->hdocs, NULL);
	ft_lstclear(&env->cmd_list, free_cmd_struct);
	ft_lstiter(env->cmd_list, print_cmd_item);
}
