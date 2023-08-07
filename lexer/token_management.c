/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:39:24 by ewehl             #+#    #+#             */
/*   Updated: 2023/08/07 12:12:33 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/**
 * @brief Set a given input string as a literal if it doesn't start with
 * a special character or isn't a whitespace.
 * 
 * @param inp Input string to process.
 * @param len Pointer to an int where the length of the literal will us stored.
 * @return int Returns the enum value for a literal.
 */
static int	set_as_lit(char *inp, int *len)
{
	int	idx;

	idx = 0;
	while (inp[idx] && !is_special_char(inp[idx]) && !ft_isspace(inp[idx]))
		idx++;
	*len = idx;
	return (LITERAL);
}

/**
 * @brief Determine the type of a given input string based on whether it 
 * starts with a special character or not. 
 * @param input Input string to process.
 * @param len Pointer to an integer where the length of the token will 
 * be stored.
 * @return int Returns the enum value corresponding to the token type.
 */
static int	get_token_type(char *input, int *len)
{
	int	enum_type;

	if (is_special_char(*input))
		enum_type = get_e_type(input, len);
	else
		enum_type = set_as_lit(input, len);
	return (enum_type);
}

/**
 * @brief Create a new token for a given input string. Allocate memory for
 * the token, get its type, and copy the input string into its value.
 * 
 * @param input Input string to create a token from.
 * @param len Pointer to an integer that stores the length of the token.
 * @return t_token* Returns a pointer to the created token.
 */
t_token	*make_token(char *input, int *len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (print_error(ERR_MEM, NULL), NULL);
	token->type = get_token_type(input, len);
	if (token->type < 0)
		return (free(token), NULL);
	token->value = ft_substr(input, 0, *len);
	if (!token->value)
		return (free(token), NULL);
	token->next = NULL;
	return (token);
}

/**
 * @brief Gets the next token from a given input string starting at a
 * specific position. 
 * 
 * @param input Input string to fetch the token from.
 * @param start Pointer to an integer that denotes the starting position 
 * 	and is updated to the next token's starting position.
 * @return t_token* Returns a pointer to the fetched token.
 */
t_token	*get_next_token(char *input, int *start)
{
	t_token	*token;
	int		len;

	len = 0;
	if (!input[*start])
		return (NULL);
	token = make_token(&input[*start], &len);
	*start += len;
	if (!token)
		return (NULL);
	return (token);
}
