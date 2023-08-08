
LIBDIR			= ./libft
LIB				= $(LIBDIR)/libft.a

INCLUDE_DIR		= ./inc

LEX_DIR			= ./lexer
PARSE_DIR		= ./parser
EXPAND_DIR		= ./expander
DEBUG_DIR		= ./debug
UTIL_DIR		= ./util
EXEC_DIR		= ./executor
BUILTIN_DIR		= ./builtins
OBJ_DIR			= ./obj
MAIN_DIR		= ./main
VPATH			= $(EXEC_DIR):$(LEX_DIR):$(PARSE_DIR):$(EXPAND_DIR):$(DEBUG_DIR):$(UTIL_DIR):$(BUILTIN_DIR)::$(MAIN_DIR)


# SRCS				= main.c
LEX_SRCS_LST		= token_management.c token_utils.c tokenlst_management.c
PARSE_SRCS_LST		= parse_brackets.c parse_redirects.c parse_simple_cmd.c parse_cmd_args.c parse_util.c check_conditional_statement.c command_tree.c combine_commands.c parse_quotes.c parse_var_set.c combine_quoted_commands.c
EXPAND_SRCS_LST		= backslash.c expand_var.c environment.c check_wildcard.c wildcard_util.c gobble.c gobble_util.c parse_wildcard.c print_export_list.c
DEBUG_SRCS_LST		= print.c
UTIL_SRCS_LST		= errors.c cmd_struct.c list_to_arr.c add_env_var.c
EXEC_SRCS_LST		= execute_tree.c file_management.c get_command.c pipe.c execute_cmd_type.c make_env_arr.c exec_pipe_utils.c here_doc.c clean_up.c
BUILTIN_SRCS_LST	= builtins.c env_echo_pwd.c set_local_var.c export_unset.c exit.c cd.c
MAIN_SRC_LIST		= minishell.c signals.c init.c parse_execute_prompt.c

LEX_SRCS		= $(addprefix $(LEX_DIR)/, $(LEX_SRCS_LST))
PARSE_SRCS		= $(addprefix $(PARSE_DIR)/, $(PARSE_SRCS_LST))
EXPAND_SRCS		= $(addprefix $(EXPAND_DIR)/, $(EXPAND_SRCS_LST))
DEBUG_SRCS		= $(addprefix $(DEBUG_DIR)/, $(DEBUG_SRCS_LST))
UITL_SRCS		= $(addprefix $(UTIL_DIR)/, $(UTIL_SRCS_LST))
EXEC_SRCS		= $(addprefix $(EXEC_DIR)/, $(EXEC_SRCS_LST))
BUILTIN_SRCS	= $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_SRCS_LST))
MAIN_SRCS		= $(addprefix $(MAIN_DIR)/, $(MAIN_SRC_LIST))

# OBJS			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS			= $(patsubst $(LEX_DIR)/%.c,$(OBJ_DIR)/%.o,$(LEX_SRCS))
OBJS			+= $(patsubst $(PARSE_DIR)/%.c,$(OBJ_DIR)/%.o,$(PARSE_SRCS))
OBJS			+= $(patsubst $(EXPAND_DIR)/%.c,$(OBJ_DIR)/%.o,$(EXPAND_SRCS))
OBJS			+= $(patsubst $(DEBUG_DIR)/%.c,$(OBJ_DIR)/%.o,$(DEBUG_SRCS))
OBJS			+= $(patsubst $(UTIL_DIR)/%.c,$(OBJ_DIR)/%.o,$(UITL_SRCS))
OBJS			+= $(patsubst $(EXEC_DIR)/%.c,$(OBJ_DIR)/%.o,$(EXEC_SRCS))
OBJS			+= $(patsubst $(BUILTIN_DIR)/%.c,$(OBJ_DIR)/%.o,$(BUILTIN_SRCS))
OBJS			+= $(patsubst $(MAIN_DIR)/%.c,$(OBJ_DIR)/%.o,$(MAIN_SRCS))

NAME			= minishell

CC				= gcc -g
CCFLAGS			= -Wall -Werror -Wextra 
# RLFLAG			= -l readline
# RLFLAG			= -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
RLFLAG			= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

RM				= rm -rf

all				: $(NAME)

bonus			: all

$(NAME)			: $(LIB) $(OBJS)
				@$(CC) $(CCFLAGS) $(RLFLAG) $(OBJS) $(LIB) -o $(NAME) 
				@echo $(NAME) made.

$(OBJ_DIR)/%.o 	: %.c
				@mkdir -p $(OBJ_DIR)
				@echo Creating $(NAME) object: $@ "\x1b[1A\x1b[M"
				@$(CC) $(CCFLAGS) -I $(LIBDIR) -I $(INCLUDE_DIR) -I $(LEX_DIR) -c -o $@ $<

$(LIB)			:
				@$(MAKE) -C $(LIBDIR)


clean			:
				@echo Cleaning $(NAME) objects
				@$(RM) $(OBJ_DIR)
				@$(MAKE) -C $(LIBDIR) clean

fclean			: clean
				@echo Cleaning $(NAME) executable
				@$(RM) $(NAME)
				@$(MAKE) -C $(LIBDIR) fclean

re				: fclean all

.PHONY 			: clean fclean library
