/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:22:22 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 12:14:40 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/**
 * @brief Checks if a given character is a space character
 *
 * The function iterates over an array of space characters defined in SPACE_ARR.
 * If the given character matches any of these, it is considered a 
 * space character.
 *
 * @param c The character to check
 * @return int Returns 1 if the character is a space character, 0 otherwise
 */
int	ft_isspace(char c)
{
	int		idx;
	char	*sp;

	idx = 0;
	sp = SPACE_ARR;
	while (sp[idx] && c)
	{
		if (c == sp[idx])
			return (1);
		idx++;
	}
	return (0);
}

/**
 * @brief Checks if a given character is a special character
 *
 * The function iterates over an array of special characters defined 
 * in SPEC_CHAR_ARR. If the given character matches any of these or is a 
 * space character, it is considered a special character.
 *
 * @param c The character to check
 * @return int Returns the character if it's a special character, 0 otherwise
 */
int	is_special_char(char c)
{
	int		idx;
	char	*s_chars;

	idx = 0;
	s_chars = SPEC_CHAR_ARR;
	while (s_chars[idx] && c)
	{
		if (s_chars[idx] == c || (ft_isspace(c)))
			return (c);
		idx++;
	}
	return (0);
}

/**
 * @brief Checks if the given string starts with a double operator
 *
 * The function checks if the string begins with one of the defined double 
 * operators: '<<', '>>', '||', or '&&'. If so, it adjusts the length and 
 * returns the respective operator type. If the string starts with '&', 
 * but not '&&', it adjusts the length and returns the LITERAL type. If none 
 * of the above conditions are met, it decrements the length and returns 0.
 *
 * @param str A pointer to the current character in a command string
 * @param len A pointer to an integer representing the length of the current 
 * 			operator
 * @return int The identified type of the double operator, or 0
 */
static int	check_double_op(char *str, int *len)
{
	if (*str == INF_RED)
	{
		if (*(str + 1) && *(str + 1) == INF_RED)
			return ((*len)++, SMALLER_2);
		return (SMALLER);
	}
	else if (*str == OUTF_RED)
	{
		if (*(str + 1) && *(str + 1) == OUTF_RED)
			return ((*len)++, GREATER_2);
		return (GREATER);
	}
	else if (*str == IS_PIPE)
	{
		if ((*str + 1) && (*(str + 1) == IS_PIPE))
			return ((*len)++, PIPE_2);
		return (PIPE);
	}
	else if (*str == '&')
	{
		if ((*str + 1) && *(str + 1) == '&')
			return ((*len)++, AMP_2);
		return ((*len)++, LITERAL);
	}
	return ((*len)--, 0);
}

/**
 * @brief Identify the type of the current character in a command string
 * 
 * The function takes a character and identifies its type. The type can 
 * be any of the defined values (SQ, DQ, BRC, BRO, AST, DLR_SIGN, BACKSLASH, 
 * SC, SP) or result from a check for double operators. The length variable is 
 * set to 1 for all types except when the character belongs to a 
 * double operator, in which case the length is adjusted in the check_double_op 
 * function.
 *
 * @param str A pointer to the current character in a command string
 * @param len A pointer to an integer representing the length of the current 
 * 			operator
 * @return int The identified type of the current character
 */
int	get_e_type(char *str, int *len)
{
	int	type;

	*len = 1;
	if (*str == S_QUOTE)
		type = SQ;
	else if (*str == D_QUOTE)
		type = DQ;
	else if (*str == BR_CLOSED)
		type = BRC;
	else if (*str == BR_OPEN)
		type = BRO;
	else if (*str == ASTERIKS)
		type = AST;
	else if (*str == DOLLAR)
		type = DLR_SIGN;
	else if (*str == ESC_BS)
		type = BACKSLASH;
	else if (*str == SEMICOLON)
		type = SC;
	else if (ft_isspace(*str))
		type = SP;
	else
		type = check_double_op(str, len);
	return (type);
}
