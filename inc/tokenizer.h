/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ewehl <ewehl@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:44:36 by ewehl         #+#    #+#                 */
/*   Updated: 2023/06/17 18:11:18 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define SPACE_ARR		"\t\n\v\f\r "
# define SPEC_CHAR_ARR	"$\"'()*<>|&\\;"

/*	TOKENLST_MANAGEMENT	*/
void	init_tlst(t_token_lst *tlist);
void	make_token_list(t_token_lst	*tlist, char *str, int len);
void	add_node(t_token_lst **tlist, t_token *node);
void	print_token_lst(t_token_lst tlist);
void	free_token_struct(t_token_lst *token);

/*	TOKEN_MANAGEMENT	*/
t_token	*make_token(char *input, int *len);
t_token	*get_next_token(char *input, int *start);

/*	TOKEN_UTILS			*/
int		ft_isspace(char c);
int		is_special_char(char c);
int		get_e_type(char *str, int *len);

#endif