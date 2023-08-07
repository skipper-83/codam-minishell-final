/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 23:45:41 by albertvanan       #+#    #+#             */
/*   Updated: 2023/08/07 15:29:55 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// MEMORY ERRORS
# define ERR_MEM "error allocating memory"

// CONDITIONAL STATEMENTS ERRORS
# define ERR_EXP_OPERATOR "expected operator"
# define ERR_EXP_EXPRESSION "expected expression"
# define ERR_CLOSE_PAR "expected ')'"
# define ERR_EXP_EOL "expected end of line"
# define ERR_TOKEN_UNEXP "unexpected token"

// PARSE ERROR

# define ERR_QUOTE_UNBALANCE "Expected closing quote"
# define ERR_PARSE_ERROR "Parse error near token "

// EXEC	ERRORS

# define CMD_NF	"command not found"
# define DUP_ERR "error dupping"
# define PIP_ERR "error piping"
# define INF_ERR "error opening infiles"
# define FORK_ERR "error forking process"
# define PERM_DEN "permission denied"
# define OUTF_ERR "error opening outfiles"
# define NO_FILE_DIR "no such file or directory"
# define EXECVE_ERR "error executing command"
# define IS_DIR "is a directory"

void	parse_error(void *param, char *description);
void	print_error(char *msg, char *msg2);
void	mem_error(void);

#endif