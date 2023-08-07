/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gobble.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 00:15:58 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/02 22:22:12 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include "parse.h"

/**
 * @brief	Open directory. If no path has been found by get_path() 
 * 			(wich is called before) this by the caller function, use the cwd. 
 * 			Else, use the path that is in first->path.
 *			Additionaly, add whatever was after the path in the original command 
 * 			to the first item of the wildcard: 
 * 			the wildcard list for ./a.* would have been ./a. -> * 
 * 			and now becomes a. -> * with the path out into cmd->path.
 * 
 * @param dir pointer to directory to be opened
 * @param first the first command that constituted the wildcard sequence
 * @param wc pointer to the wildcard list
 * @return int 
 */
static int	get_dir(DIR **dir, t_cmd *first, t_list **wc)
{
	char	dir_name[PATH_MAX];

	if (first->path == NULL)
		getcwd(dir_name, PATH_MAX);
	else
	{
		if (first->literal[0])
		{
			free((*wc)->content);
			(*wc)->content = ft_strdup(first->literal);
			if ((*wc)->content == NULL)
				return (mem_error(), 0);
		}
		else
			ft_lstdel_item(wc, *wc, free);
		ft_strlcpy(dir_name, first->path, ft_strlen(first->path));
	}
	*dir = opendir(dir_name);
	return (1);
}

/**
 * @brief Add an item gobbled up by the wildcard to the command list
 * 
 * @param first first command of wc sequence, used for path
 * @param item the directory item to be checked
 * @param start the first command in the list
 * @param last the next command after the wildcard sequence
 * @return int 
 */
static int	add_gobble(t_cmd *first, struct dirent *item, \
										t_list **start, t_list *last)
{
	t_cmd	*wrk_cmd;
	t_list	*wrk_li;
	char	*wrk;

	if (first->path != NULL)
		wrk = ft_strjoin(first->path, item->d_name);
	else
		wrk = ft_strdup(item->d_name);
	if (wrk == NULL)
		return (mem_error(), 0);
	wrk_cmd = cmd_from_char(wrk);
	wrk_li = ft_lstnew(wrk_cmd);
	if (wrk_cmd == NULL || wrk_li == NULL)
		return (mem_error(), (*start)->next = last, 0);
	ft_lstadd_back(start, wrk_li);
	return (1);
}

/**
 * @brief	Loop over a directory and check if an entry matches the wildcard. 
 * 			If so, add it to the command list with add_gobble();
 * 
 * @param dir the directory to be gobbled
 * @param start the first command in the list
 * @param last the next command after the wildcard sequence
 * @param wc the wildcard
 * @return int 
 */
static int	gobble_loop(DIR *dir, t_list **start, t_list *last, t_list *wc)
{
	struct dirent	*dir_item;
	t_cmd			*first;

	dir_item = readdir(dir);
	first = (t_cmd *)(*start)->content;
	while (dir_item != NULL)
	{
		if (dir_item->d_name[0] != '.')
			if (check_wildcard(dir_item->d_name, wc))
				if (!add_gobble(first, dir_item, start, last))
					return (0);
		dir_item = readdir(dir);
	}
	closedir(dir);
	return (1);
}

static int	return_gobble(t_list **start, t_list *last, t_cmd *prev, t_list *wc)
{
	t_list	*wrk_li;

	if (((*start)->next != NULL))
	{
		wrk_li = (*start)->next;
		ft_lstdel_item(start, *start, free_cmd_struct);
		*start = wrk_li;
		sort_gobble_list(*start);
		if (prev->type >= SMALLER && prev->type <= GREATER \
											&& ft_lstsize(*start) > 1)
		{
			ft_lstiter(wc, print_wc_to_stderr);
			ft_putendl_fd(": ambiguous redirect", 2);
			return (ft_lstlast(*start)->next = last, 0);
		}
	}
	else
		reset_cmd((t_cmd *)(*start)->content, wc);
	ft_lstlast(*start)->next = last;
	return (1);
}

/**
 * @brief	Function to gobble up filenams from the directory pointed to by
 * 			path or the cwd. If command is a heredoc, it resets the string
 * 			that was parsed as a wildcard, because that string is the limiter
 * 			and is not used for gobbling.
 * 			Otherwise, it will get the path (cwd or path specified), open that
 * 			directory, and loop over all items in that directory to check if it
 * 			matches the wildcard passed as [wc]. Adds all items gobbled up to 
 * 			the command list.
 * 
 * @param wc the wildcard list
 * @param start the first command to be checked
 * @param last pointer to next command in the list, which would be the next of 
 * 				the last item that is gobbled up
 * @param prev the previous item in the command list, used to check wheter the 
 * 				command is a redirection.
 * @return int 
 */
int	gobble(t_list **wc, t_list **start, t_list *last, t_cmd *prev)
{
	DIR				*dir;

	if (prev->type == SMALLER_2)
		return (reset_cmd((t_cmd *)(*start)->content, *wc), 1);
	if (!get_path((t_cmd *)(*start)->content))
		return (mem_error(), 0);
	if (!get_dir(&dir, (t_cmd *)(*start)->content, wc))
		return (0);
	if (dir == NULL)
		return (reset_cmd((t_cmd *)(*start)->content, *wc));
	(*start)->next = NULL;
	if (!gobble_loop(dir, start, last, *wc))
		return (0);
	return (return_gobble(start, last, prev, *wc));
}
