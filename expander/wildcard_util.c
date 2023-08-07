/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:28:02 by albertvanan       #+#    #+#             */
/*   Updated: 2023/07/06 12:57:16 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

/**
 * @brief	Counts the amount of times a pattern is repeated in list of wildcard
 * 			criteria.
 * 
 * @param wc the list item with the criterium
 * @return int the amount of repetitions (0 of the pattern is there only once)
 */
int	count_pattern_repetitions(t_list *wc)
{
	int		i;
	char	*pattern;

	i = 0;
	while (1)
	{
		if (wc->next && wc->next->next)
		{
			pattern = (char *)wc->next->next->content;
			if (!ft_strncmp((char *)wc->content, pattern, ft_strlen(pattern)))
				i++;
			else
				break ;
			wc = wc->next->next;
		}
		else
			break ;
	}
	return (i);
}

/**
 * @brief	Counts the amount of times a pattern is repeated in an input
 * 			string, from the given index onwards.
 * 
 * @param wc the list item with the pattern
 * @param pat_reps the amount of times the pattern is repeated in the criteria
 * @param input the input string
 * @param i pointer to index of input string
 * @return int amount of repetitions (0 if patterne is there only once)
 */
int	count_input_reps(t_list *wc, int pat_reps, char *input, int *i)
{
	char	*next_pat;
	char	*pattern;
	int		ret;

	*i = 0;
	ret = -1;
	next_pat = NULL;
	pattern = (char *)wc->content;
	if (pat_reps == 0 && ft_strncmp(input, pattern, ft_strlen(pattern)))
		return (-1);
	while ((*i)++ < pat_reps)
		wc = wc->next->next;
	if (wc->next && wc->next->next)
		next_pat = (char *)wc->next->next->content;
	*i = 0;
	while (input[*i])
	{
		if (next_pat != NULL && \
					!ft_strncmp(&input[*i], next_pat, ft_strlen(next_pat)))
			break ;
		if (!ft_strncmp(&input[*i], pattern, ft_strlen(pattern)))
			ret++;
		(*i)++;
	}
	return (ret);
}

/**
 * @brief	Print a wildcard to the stderr. Used by an error handler in ft_lstiter.
 * 
 * @param param 
 */
void	print_wc_to_stderr(void *param)
{
	ft_putstr_fd((char *)param, 2);
}
