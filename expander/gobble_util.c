/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gobble_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 00:24:30 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/02 16:00:57 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

/**
 * @brief	Sorts the list gobbled up by gobble() alfabetically. Note: when the
 * 			function is called, the next item of the last list item is still NULL
 * 			it is only after this function has run that this is replaced by the pointer
 * 			to the next item in the command list.
 * 
 * @param head 
 */
void	sort_gobble_list(t_list *head)
{
	void	*swap;
	t_list	*wrk;

	wrk = head;
	while (wrk->next != NULL)
	{
		ft_max(ft_strlen(((t_cmd *)wrk->content)->literal), \
						ft_strlen(((t_cmd *)wrk->next->content)->literal));
		if (ft_strcmp(((t_cmd *)wrk->content)->literal, \
						((t_cmd *)wrk->next->content)->literal) > 0)
		{
			swap = wrk->content;
			wrk->content = wrk->next->content;
			wrk->next->content = swap;
			wrk = head;
		}
		else
			wrk = wrk->next;
	}
}

/**
 * @brief	Resets the command to its original state when nothing is 
 * 			gobbled up by the wildcard.
 * 
 * @param cmd 
 * @param wc 
 * @return int 
 */
int	reset_cmd(t_cmd *cmd, t_list *wc)
{
	char	*reset_command;
	char	*wc_cmd;

	wc_cmd = get_wc_string(wc);
	if (wc_cmd == NULL)
		return (mem_error(), 0);
	if (cmd->path != NULL)
	{
		reset_command = ft_strjoin(cmd->path, wc_cmd);
		free (wc_cmd);
	}
	else
		reset_command = wc_cmd;
	free (cmd->path);
	free (cmd->literal);
	cmd->path = NULL;
	cmd->literal = reset_command;
	cmd->type = LITERAL;
	if (reset_command == NULL)
		return (mem_error(), 0);
	return (1);
}

/**
 * @brief	Used by gobble(): creates new command node
 * 			from string input. Called every time a new
 * 			name is gobbled up from a directory by a wildcard search.
 * 
 * @param literal 
 * @return t_cmd* 
 */
t_cmd	*cmd_from_char(char *literal)
{
	t_cmd	*res;

	res = ft_calloc(1, sizeof(t_cmd));
	if (res == NULL)
		return (NULL);
	res->literal = ft_strdup(literal);
	if (res->literal == NULL)
		return (free(res), NULL);
	res->type = LITERAL;
	free(literal);
	return (res);
}

/**
 * @brief	Used to reset a command when nothing has been gobbled up in 
 * 			a wildcard search. Takes the list that constitutes a wildcard
 * 			and pastes it together to be used as the literal.
 * 
 * @param wc 
 * @return char* 
 */
char	*get_wc_string(t_list *wc)
{
	int		len;
	t_list	*wrk;
	char	*r;
	int		i;

	len = 1;
	wrk = wc;
	while (wrk)
	{
		len += ft_strlen((char *)wrk->content);
		wrk = wrk->next;
	}
	r = ft_calloc(len, sizeof(char));
	if (r == NULL)
		return (NULL);
	wrk = wc;
	i = 0;
	while (wrk)
	{
		ft_strlcpy(&r[i], (char *)wrk->content, \
					ft_strlen((char *)wrk->content) + 1);
		i += ft_strlen(wrk->content);
		wrk = wrk->next;
	}
	return (r);
}
