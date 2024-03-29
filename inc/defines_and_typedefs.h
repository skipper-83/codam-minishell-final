/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_and_typedefs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 23:46:56 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 22:59:25 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_AND_TYPEDEFS_H
# define DEFINES_AND_TYPEDEFS_H

# define PROMPT "\1\e[1m\e[31m\2cEAsh\1\e[0m\2 > "

# define WILDCARD 42 // *
# define PAR_OPEN "("
# define PAR_CLOSE ")"

# define DOLLAR			36 	// $
# define ESC_BS			92 	// /
# define S_QUOTE		39 	// '
# define D_QUOTE		34	// "
# define BR_OPEN		40	// (
# define BR_CLOSED		41	// }
# define ASTERIKS		42	// *
# define INF_RED		60	// <
# define HEREDOC		"<<"
# define OUTF_APP_RED	">>"
# define OUTF_RED		62	// >
# define IS_PIPE		124 // |
# define IS_OR			"||"
# define D_AMP			"&&"
# define SEMICOLON		59	// ;

# define RED "\001\e[0;31m\002"
# define GREEN "\001\e[0;32m\002"
# define YELLOW "\001\e[0;33m\002"
# define BLUE "\001\e[34m\002"
# define ENDC "\001\e[0m\002"

typedef enum e_token_type
{
	ERR = -1,
	LITERAL,
	SQ,
	DQ,
	BRO,
	BRC,
	AST,
	SMALLER,
	SMALLER_2,
	GREATER_2,
	GREATER,
	BACKSLASH,
	PIPE,
	PIPE_2,
	AMP_2,
	SC,
	SP,
	DLR_SIGN,
}	t_token_type;

typedef struct token
{
	t_token_type	type;
	char			*value;
	struct token	*next;
}	t_token;

typedef struct token_lst
{
	t_token	*head;
	int		len;
}	t_token_lst;

typedef struct s_cmd
{
	char			*literal;
	t_list			*args;
	t_list			*infiles;
	t_list			*outfiles;
	t_list			*vars;
	t_token_type	quote_type;
	int				is_subtree;
	int				is_var_setter;
	t_token_type	type;
	int				fd;
	int				pid;
	int				infile_fd;
	int				outfile_fd;
	char			*path;
	char			**arg_arr;
}	t_cmd;

typedef struct s_env
{
	t_list		*cmd_list;
	t_list		*hdocs;
	t_list		*env_vars;
	t_list		*open_fds;
	t_list		*local_vars;
	t_btnode	*cmd_tree;
	int			last_exit;
	int			verbose;
	int			test;
}	t_env;

typedef struct s_env_var
{
	char	*key;
	char	*value;
	char	export;
}	t_env_var;

#endif