/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_wildcard.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/22 22:23:05 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/08/01 18:11:31 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

/**
 * @brief	Skip through input string untill the next pattern is found.
 * 			return 0 if end of string is reached before that.
 * 
 * @param wc list item containg the current pattern 
 * @param i index of input string
 * @param input input string
 * @return	int 0 if end of string is reached before pattern is found, 1 if 
 * 			pattern is found. 			
 */
static int	skip_until_pattern(t_list *wc, int *i, char *input)
{
	char	*next_pattern;

	while (1)
	{
		if (!input[*i])
			return (0);
		next_pattern = (char *)wc->next->content;
		if (!ft_strncmp(&input[*i], next_pattern, ft_strlen(next_pattern)))
			break ;
		(*i)++;
	}
	return (1);
}

/**
 * @brief	Count how many times the pattern of the current list item is repeated
 * 			in the wildcard criteria, and count how many times it is repeated in 
 * 			the input string. If there are less input repetitions than criteria
 * 			repetitions, return 0.
 * 			After this check, reset the index to the end of the last repetion of the
 * 			criterium, and point the linked list to the next pattern after the ones
 * 			that were repeated.
 * 
 * @param i 
 * @param wc 
 * @param pattern_reps 
 * @param input 
 * @return int 
 */
static int	find_pattern(int *i, t_list **wc, int pattern_reps, char *input)
{
	int		len;
	char	*criterium;
	int		input_reps;
	int		j;

	criterium = (char *)(*wc)->content;
	len = ft_strlen(criterium);
	input_reps = count_input_reps(*wc, pattern_reps, &input[*i], &j);
	if (input_reps < pattern_reps)
		return (0);
	*i += j;
	while (ft_strncmp(&input[*i], criterium, len))
		(*i)--;
	*i += len;
	while (pattern_reps--)
		*wc = (*wc)->next->next;
	return (1);
}

/**
 * @brief	Check if a pattern matches all criteria. If there is only
 * 			one item in the wildcard list, it performs a simple string
 * 			compare (because wc:[pattern], input[patternpattern] should be 0).
 * 			In all other cases check how often the current pattern is repeated
 * 			in the wildcard criteria, and check how often it repeats in the input.
 * 			This is done in find_pattern(). 
 * 			If the last wildcard item is found and there are still characters in 
 * 			the string, the function returns 0.
 * 
 * @param wc 
 * @param i 
 * @param input 
 * @param first 
 * @return int 
 */
static int	check_pattern(t_list **wc, int *i, char *input, int first)
{
	char	*criterium;
	int		len;

	criterium = (char *)(*wc)->content;
	len = ft_strlen(criterium);
	if (first && (*wc)->next == NULL)
		if (ft_strncmp(input, criterium, len))
			return (0);
	if (!find_pattern(i, wc, count_pattern_repetitions(*wc), input))
		return (0);
	if ((*wc)->next == NULL && input[*i])
		return (0);
	return (1);
}

/**
 * @brief	Checks if [input] fits within the criteria of [wildcard].
 * 			loops through the linked list of wildcard criteria, that
 * 			consists of a succesion of * (n characters) and patterns
 * 			so wildcard:[*pattern] would mean input[123pattern]
 * 			is correct.
 * 			When a * is found, function will skip through input string
 * 			untill the pattern of the next list item is found, unless it
 * 			is the last item, in that case it will return 1.
 * 			When a pattern is met, the function will check with check_pattern
 * 			wether the pattern meets all criteria. Especially repetition is 
 * 			relevant: wildcard:[pattern*pattern] should return 1 when the
 * 			input is[patternpatternpatternpattern], as 'n' characters can 
 * 			contain the pattern itself, even if its repeated.
 * 
 * 
 * @param input	input string
 * @param wildcard made by parse_wildcard() 
 * @return int 1 if input fits criteria, 0 if it doesn't
 */
int	check_wildcard(char *input, t_list *wildcard)
{
	t_list	*wc;
	int		i;

	i = 0;
	wc = wildcard;
	while (wc)
	{
		if (*(char *)wc->content == WILDCARD)
		{
			if (wc->next == NULL)
				return (1);
			if (!skip_until_pattern(wc, &i, input))
				return (0);
		}
		else
		{
			if (!check_pattern(&wc, &i, input, wildcard == wc))
				return (0);
		}
		wc = wc->next;
	}
	return (1);
}
